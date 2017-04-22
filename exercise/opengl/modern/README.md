## GLFW

GLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口。它允许用户创建OpenGL上下文，定义窗口参数以及处理用户输入，这正是我们需要的。

## GLEW(OpenGL Extension Wrangler Library)

因为OpenGL只是一个标准/规范，具体的实现是由驱动开发商针对特定显卡实现的。由于OpenGL驱动版本众多，它大多数函数的位置都无法在编译时确定下来，需要在运行时查询。任务就落在了开发者身上，开发者需要在运行时获取函数地址并将其保存在一个函数指针中供以后使用。

幸运的是，有些库能简化取得地址的过程，其中GLEW是目前最新，也是最流行的库。

## GLSL

[着色器](https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/05%20Shaders/)

着色器是使用一种叫GLSL的类C语言写成的。GLSL是为图形计算量身定制的，它包含一些针对向量和矩阵操作的有用特性。

着色器的开头总是要声明版本，接着是输入和输出变量、uniform和main函数。每个着色器的入口点都是main函数，在这个函数中我们处理所有的输入变量，并将结果输出到输出变量中。

一个典型的着色器有下面的结构：

```glsl
#version version_number

in type in_variable_name;
in type in_variable_name;

out type out_variable_name;

uniform type uniform_name;

int main(){
    // 处理输入并进行一些图形操作
    ...
    // 输出处理过的结果到输出变量
    out_variable_name = weird_stuff_we_processed;
}
```

基础数据类型: `int` / `float` / `double` / `unint` / `bool`

向量: GLSL中的向量是一个可以包含有1、2、3或者4个分量的容器，分量的类型可以是前面默认基础类型的任意一个。它们可以是下面的形式（n代表分量的数量）--
| 类型 | 含义 |
| --- | --- |
| `vecn` | 包含`n`个 float 分量的默认向量 |
| `bvecn` | 包含`n`个 bool 分量的向量 |
| `ivecn` | 包含`n`个 int 分量的向量 |
| `uvecn` | 包含`n`个 unsigned int 分量的向量 |
| `dvecn` | 包含`n`个 double 分量的向量 |

向量访问:
* 空间 -- `.x` / `.y` / `.z` / `.w`
* 颜色 -- `.r` / `.g` / `.b` / `.a`
* 纹理 -- `.s` / `.t` / `.p` / `.q`
* 重组方式访问 -- `.xyxx`

输入和输出: `in` / `out` 关键字

每个着色器使用这两个关键字设定输入和输出，只要一个输出变量与下一个着色器阶段的输入匹配，它就会传递下去。但在顶点和片段着色器中会有点不同。

如果我们打算从一个着色器向另一个着色器发送数据，我们必须在发送方着色器中声明一个输出，在接收方着色器中声明一个类似的输入。当类型和名字都一样的时候，OpenGL就会把两个变量链接到一起，它们之间就能发送数据了（这是在链接程序对象时完成的）。

| 后缀 | 含义 |
| --- | --- |
| `f` | 函数需要一个float作为它的值 |
| `i` | 函数需要一个int作为它的值 |
| `ui` | 函数需要一个unsigned int作为它的值 |
| `3f` | 函数需要3个float作为它的值 |
| `fv` | 函数需要一个float向量/数组作为它的值 |

