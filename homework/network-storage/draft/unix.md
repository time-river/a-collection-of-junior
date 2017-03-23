谈及操作系统的历史，总少不了类 Unix 系统。文件管理作为操作系统的一项重要功能，必然与其相伴相随。

![lj-VFS](lj-VFS)
    这是我在网上找到的一幅图，密密麻麻的线条，我看着也头疼。

    其实可以使用这张图替代
![VFS](vfs.jpg)

    VFS 这层抽象，为上层应用提供了如下功能：
    不同的文件系统，却有
    * 相同的文件描述结构——vnode: virtual node: abstract file object,
    * 统一的文件操作——All operations to fs's and files done through VFS/vnode in-terface
    --对不同的文件系统系统抽象，为上层应用提供统一的接口

    隐藏不同硬件设备的细节，为内核提供统一的 IO 操作接口

    Some Definitions
    * superblock: fs summary, pointers to other information
    * inode: on-disk structure containing information about a file
    * indirect block: block containing pointers to other blocks
    * metadata: everything that is not user data, including directory entries

    Disk characteristics
    * track: contiguous region, can be read at manumux speed
    * seek time: time to move the head between different tracks
    * rotational delay: time for part of track to move under head
    * fixed per I/O overhead means bigger I/Os are better

In the beginning: System V FS(S5FS)(c. 1974)
    * First UNIX file system, referred to as "FS"
    * Disk layout: __superblock, inodes__, followed by everything else
    * 512-1024 byte block size, no fragments
    * Super simple - and super slow! 2-5% of raw disk bandwidth
![fs](fs.png)
缺点就是对磁盘感知太差, 目录放的乱七八糟, 文件放的乱七八糟, inode也放的乱七八糟. 假设我们要访问 /home/user/workspace/a/b/c/work.txt, 我们要先在根目录下找到home的inode, 再从inode中找到block, 再去block中找user......一次次重复这个操作，至少20多次磁盘访问, 如果这些block随机分布, 那么磁盘访问就很慢了. 如果能把这些东西都组织在很近的一块地方, 那么速度就快了.
    (
     __空间 VS 速度__
     A block size larger than 512 bytes is desirable for speed. However, because UNIX file systems usually contain a very large number of small files, much larger blocks would cause excessive internal fragmentation. 
     [Blocks and fragments](https://webservices.ignou.ac.in/virtualcampus/adit/course/cst101/block4a/unit1/cst101-bl4a-u1-11.htm)
    )

    [Background(https://github.com/gzc/isystem/blob/master/papers/fs/ffs.md#ffs-disk-awareness-is-the-solution)

速度导致改进
A 150MB traditional UNIX file system consists of 4 MB of inodes followed by 146 MB of data.This organization segregates the inode information from data; thus accessing a file normally incurs a long seek from the file's inode to its data. File in a sigle directory are not typically allocated consecutive slots in the 4 mb of inodes, causing many non-consecutive blocks of inodes to be accessed when executing operations on the inodes of several files in a directory.

The first work at Berkeley on the UNIX file system attempted to improve both reliability and throughput.

1. __Why reliability?__

The reliability was improved by staging modification to critical file system imformation so that they could either be completed or repaired cleanly by a program after a crash.

The file system performance wwas improved by a factor of more than two by changing the basic block size from 512 to 1024 bytes. Two factors: 1. ???

文件的随机存放导致速度不快
FFS: Disk Awareness Is The solution
核心思想就是如何做到"Disk Aware".
Berkeley Fast File Systm(FFS or UFS)(c. 1984)
    * Metadata spread throughout the disk in "cylinder groups"
        * 每个柱面都有元信息
        * 一个cylinder groud(柱面组)由3个柱面组成
        * 如果两个文件在同一个group，FFS 能够保证对这两个文件的顺序访问很快
        * bit map insteads of system's free list
    * Block size 4KB minimum, frag size 1KB (to avoid 45% wasted space)
        * 磁盘利用率与速度
        * The 4.2BSD solution is to use two block sizes for files which have no indirect blocks: all the blocks of a file are of a large block size (such as 8K), except the last. The last block is an appropriate multiple of a smaller fragment size (for example, 1024) to fill out the file. Thus, a file of size 18,000 bytes would have, two 8K blocks and one 2K fragment (which would not be filled completely).
    * Physical disk parameters taken into account
        * in the past, no information about either the physical characterstics of the mass storage device, or the hardware that interacts with it. A goal of the new file system is to parameterize the processor capabilities and mass storage characteristics so that blocks can be allocated in an optimum configuration dependent way.
    * Much better performance: 14% - 17% of raw disk bandwidth
    * Also 256 byte file names, file locks, symlinks, rename(), and quotas
        * 之前的文件系统最多只能支持8chars的文件命名，支持长文件名
    * fsck (file system check)

    Improvements to FFS/UFS
    * 198?: Logging
    * 1991: Improvements to block allocation and read ahead policy
        * 如何分配directory: 选择那些directory分配的少, free inodes多的group,达到均衡目录和将来快速分配创建文件的目的.
        * 如何创建文件: 确保数据和inode在相同的group, 防止花大量时间查找inode和数据块.把属于同一个目录的文件放一起. 如果用户创建了 /dir1/1.txt, /dir1/2.txt, /dir1/3.txt, and /dir99/4.txt, FFS会把前面3个文件放在同一个group. 因为我们假定同一个文件夹下的文件很有可能被连续访问, 合情合理.
        * read ahead policy:Readahead is a system call of the Linux kernel that loads a file's contents into the page cache. This prefetches the file so that when it is subsequently accessed, its contents are read from the main memory (RAM) rather than from a hard disk drive (HDD), resulting in much lower file access latencies.
    * 1999: Soft updates
        * Soft updates is an approach to maintaining file system meta-data integrity in the event of a crash or power outage. Soft updates work by tracking and enforcing dependencies among updates to file system meta-data. 

Log-structured File System(LFS)(c. 1991)
    * All on-disk data in the form of sequential log entries
        * 使用日志的方式即是数据，日志就是文件系统，文件系统就是日志
        * 当时设计LFS基于这么一个假设：随着内存的增大，文件系统读缓存的命中率会很高，因此写IO将替代读IO成为系统瓶颈。为了解决写IO的瓶颈，LFS中数据和元数据修改都是追加到日志末尾，没有原地更新，这种方法能将磁盘的随机写转化成顺序写，重复利用写带宽。
        * SSD，但顺序读性能下降——如果文件频繁被修改，那么文件的数据库将会分散到各处，文件顺序读的性能明显下降。
    * Crash recovery rolls forward from last checkpoint
    * 70% of raw disk write bandwidth, buf FFS can do as well
        * Unix file systems typically can use only 5-10%

Over the last decade CPU speeds have increased dramatically while disk access times have only improved slowly. This trend is likely to continue in the future and it will cause more and more applications to become disk-bound. To lessen the impact of this problem. To lessen the impact of this problem...
Log-structured file systems are based on the assumption that files are cached in main memory and that increasing memory sizes will make the caches more and more effiective at satisfying read requests. As a result, disk traffic will become dominated by writes. —— Resolution: A log-structed file system writes all new information to disk in a sequential structure called the log. This approach increases write performance dramatically by eliminating almost all seeks. The sequential nature of the log also permits much faster crash recovery: current Unix file systems typically must scan the entire disk to restore consistency after a crash, but a log-structured file system need only examine the most recent portion of the log.

__Key: LOG__
The notion of logging is not new, and a number of recent file systems have incorporated a log as an anxiliary structure to speed up writes and crash recovery. However, these other systems use the log only for temporary storage; the permanent home for information is in a traditional random-access storage structure on disk. In contrast, a log-structured file system stores dta permanently in the log: there is no other structre on disk. The log is the only structure on disk; it contains indexing information so that filesystem can be read back from the log efficiently.

当前文件系统存在的问题之一：
写入小文件，少于 5% 的带宽被使用，都浪费在寻道(seeking)上了。
之二：同步写入时，应用必须等待写入完，而不是在后台继续其他操作。

---
为了操作更有效率，LSF 需要大量的空闲空间来写入新的数据。但这点对LSF来说是一个很大的挑战。In this paper we present a solution based on large extents called segments, where a segment cleaner process continually regenerates empty segments by compressing the live data from heavily fragmented segments.


The filesystem used in Minix, which was originally developed for educational purposes, had some significant limitations. The maximum file size was 64MB and the maximum filename length was 14 characters. For some Linux pioneers, these limits were eventually unsustainable, and they started to think about a new, native Linux filesystem. Linus integrated the VFS (virtual filesystem) layer into kernel version 0.96a, which facilitated adding additional filesystems.
In version 0.96c, the first member of the ext filesystem (FS) family saw the light of the Linux world. Rémy Card, the main architect, was inspired by the design of the UFS (Unix filesystem). Filenames were now allowed to be 255 characters on a filesystem of up to 2GB.
Although ext represented an improvement over the Minix filesystem, it still had a number of elements the developers absolutely hated, such as only one timestamp, instead of the three typically in use today, and the use of linked lists for free space, which quickly led to fragmentation and poor performance.
The replacement of ext was therefore inevitable and not long in coming. The successor, ext2, became part of the Linux kernel in version 0.99.7.
[The ext Filesystem](http://www.linux-magazine.com/Issues/2013/156/The-ext-Filesystem)

ext2 and ext3(c. 1993 - present)
    * FFS like, no fragments
    * ext3 adds journaling, removes need for fsck on crash
        * 假如说，我们在编辑文件时，突然停电了、或系统被锁定被迫得重启，会出现什么后果？轻则文件丢失部分内容，重则整个文件内容混乱，更有甚者文件系统直接崩溃。
        * 日志文件系统就是专为那些厌倦了一直盯着启动时 fsck（即文件系统一致性检查）的人而设计的。
        * 為了避免上述提到的檔案系統不一致的情況發生，因此我們的前輩們想到一個方式， 如果在我們的 filesystem 當中規劃出一個區塊，該區塊專門在記錄寫入或修訂檔案時的步驟， 那不就可以簡化一致性檢查的步驟了？也就是說：
        * 預備：當系統要寫入一個檔案時，會先在日誌記錄區塊中紀錄某個檔案準備要寫入的資訊；
        * 實際寫入：開始寫入檔案的權限與資料；開始更新 metadata 的資料；
        * 結束：完成資料與 metadata 的更新後，在日誌記錄區塊當中完成該檔案的紀錄。
        * 在這樣的程序當中，萬一資料的紀錄過程當中發生了問題，那麼我們的系統只要去檢查日誌記錄區塊， 就可以知道哪個檔案發生了問題，針對該問題來做一致性的檢查即可，而不必針對整塊 filesystem 去檢查， 這樣就可以達到快速修復 filesystem 的能力了！這就是日誌式檔案最基礎的功能
        * 故障恢复能力
        * 并不是第一个日志式文件系统
        * The system utility fsck (for "file system consistency check") is a tool for checking the consistency of a file system in Unix and Unix-like operating systems
    * Primary attributes are simplicity, performance, and recoverability
    * __ext2 often beats all other file system in performance tests__

近年来 ext2/3 暴露出了一些扩展性问题，于是便催生了 ext4 

Write Anywhere File Layout(WAFL)(c. 1994)
    * Copy-on-write, checksummed, always consistent on-disk format
        * Block-Level Checksum(硬盘区块验证系统)保障资料读取的正确性
        * ![copy on write](copy-on-write.png)
        * [Copy On Write](https://pthree.org/2012/12/14/zfs-administration-part-ix-copy-on-write/)
    * Metadata in file
        * In the context of Unix or Linux file systems, "metadata" is information about a file: user ID of who owns it, permissions, file type (special, regular, named pipe, etc) and which disk-blocks the file uses. That's all typically kept in an on-disk structure called an "inode".
        * 使用文件存储元数据
        * 允许在硬盘上任何地方写入元数据块
        * 使文件系统的增长变得十分容易
        * http://chusb.blog.51cto.com/113839/79275
    * Intent log in NVRAM satisfies NFS sync semantics and performance
        * 采用有电池保护的 NVRAN(非易失性闪存)来担任其日志，在非正常断电或关机时，重新开机后可在2分钟内开始提供服务，不需要执行文件系统检查，也不用担心文件系统损坏。
    * Revolutionary and completely underappreciated
    * File System Design for an NFS File Server Appliance

SGI'S XFS (c. 1996)
    * EFS was FFS with extents - pointers to contigous lists of blocks
    * XFS adds B+ trees to track free space, index directories, locate file blocks and inodes, also first 64-bit file system in wide use
        * 64-bit means a maximum size of 8 exabytes.（10^18)
    * Focus on scalability and streaming I/O -- 90-95% raw disk bandwidth
    * Dynamic inode allocation, logging, volume manager, muti-threaded read/writes
[](https://wizardforcel.gitbooks.io/vbird-linux-basic-4e/content/127.html)

optimized for speed and reliability, winning many speed comparsion tests
optimized for multithreading——multiple threads can operate on the same file system simultaneously.
In 2000 SGI released the XFS source code under the GNU Public License, and in the following years, many Linux distributions have added support for this file system.

JFS (c. 2000)
    * Similar to XFS with fewer B+ trees
    * Currently undergoing major hype

Veritas File System(VxFS) (c. 1988 - present)
    * Version 1: Similar to FFS plus Logging
    * Version 5: Similar to XFS/JFS
    * Main clain to fame: ported to many architectures
    * Leader in special purpose performance hacks

Reiserfs v. 1 - 4 (c. 1998 - present)
    * Designed for good small file and large directory performance
    * Constantly changing (4 on-disk formats in 6 years)
    * A little of ererything: logging, B+ trees, COW, tail-packing
    * Second only to ext2 in performance, but poorer recovery
    * Understood by few, no good papers

Zettabyte File System (ZFS) (c. 2004)
    * First fs to improve on WAFL, available in a future Solaris 10 updates
    * Built-in volume manager, file systems share storage
    * First 128-bit file System
        * ZB system
        * Project leader Jeff Bonwick said that "Populating 128-bit file systems would exceed the quantum limits of earth-based storage. 
        *  You couldn't fill a 128-bit storage pool without boiling the oceans.
    * Self-healing data, dynamic striping, mutiple block sizes, unlimitd constant-time r/w snapshots, multiple partitions...

btrfs
    * 继承 ZFS
    * 各有千秋
    * 针对 SSD 的优化支持
        * ZFS 为传统HDD设计

Solutions to common design problems
    * On-disk consistency in face of system crash
    * Large contiguous allocations
    * Metadata allocation

On-disk consistency
    * Repair after the fact - fsck (FFS, ext2) item Journal replay - write log, redo writes
    * Soft updates - per-pointer roll forward and Background
    * Always consistent - copy-on-write

Large contiguous allocations
    * Block clustering
        * 以 block 为基本单位，将磁盘划分为多个 block 。为了管理磁盘空间，文件系统需要知道哪些 block 是空闲的。
        * Ext 使用 bitmap 来达到这个目的。 Bitmap 中的每一个 bit 对应磁盘上的一个 block，当相应 block 被分配后，bitmap 中的相应 bit 被设置为 1 。这是很经典也很清晰的一个设计，但不幸的是当磁盘容量变大时，bitmap 自身所占用的空间也将变大。这就导致了扩展性问题，随着存储设备容量的增加，bitmap 这个元数据所占用的空间也随之增加。而人们希望无论磁盘容量如何增加，元数据不应该随之线形增加，这样的设计才具有可扩展性。
    * extents
        * 现代很多文件系统都采用了 extent 替代 block 来管理磁盘。 Extent 就是一些连续的 block，一个 extent 由起始的 block 加上长度进行定义。
    * Multiple block sizes

Metadata allocation
    * Fixed number, all together
    * Fixed number, statically spread throughout the disk
    * Fixed number, located Anywhere
    * Dynamically allocated, in files

Improvements:
    * metadata
    * the ability to index files for faster searches
    * new storage designs that reduce file fragmentation
    * more robust error-correction abilities
    * one of the biggest advances in file systems has been the addition of journaling

ZFS 代表” last word in file system ”，意思是此后再也不需要开发其他的文件系统了。 ZFS 的确带来了很多崭新的观念，对文件系统来讲是一个划时代的作品。
如果您比较 btrfs 的特性，将会发现 btrfs 和 ZFS 非常类似。也许我们可以认为 btrfs 就是 Linux 社区对 ZFS 所作出的回应。从此往后在 Linux 中也终于有了一个可以和 ZFS 相媲美的文件系统。
https://www.ibm.com/developerworks/cn/linux/l-cn-btrfs/
