NAME := $(shell ls -tr /home/me/NetBeansProjects/HelloWorldApp/src/ | grep -i java | awk 'BEGIN { FS = "." } END { print $$1 }')

build:
	 javac $(NAME).java
	 java  $(NAME)
	 rm *.class
