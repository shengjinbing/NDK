1. 生成的 crash信息，如果授予Sdcard权限会优先存放在`/sdcard/crashDump`下，
便于我们做进一步的分析。反之会放到目录 `/data/data/com.dodola.breakpad/files/crashDump`

Dump 日志分析
========

1. 将抓取到的日志拉取到本地中
2. 使用例子中提供的 `tools/mac/minidump_stackwalker` 工具来根据 minidump 文件生成堆栈跟踪log
```
	 ./tools/mac/minidump_stackwalk crashDump/***.dmp >crashLog.txt 
```

3. 符号解析，可以使用 ndk 中提供的`addr2line`来根据地址进行一个符号反解的过程,该工具在 
`$NDK_HOME/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-addr2line`
 
 注意：此处要注意一下平台，如果是 arm64位的 so，解析是需要使用 `aarch64-linux-android-4.9`下的工具链
```
arm-linux-androideabi-addr2line -f -C -e sample/build/intermediates/transforms/mergeJniLibs/debug/0/lib/armeabi-v7a/libcrash-lib.so 0x77e                           
//输出结果如下
Crash()

```


