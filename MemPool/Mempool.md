#STL(SGI)内存池性能的测试
这里的测试代码就是同一目录下的main.cc<br>
demo.cc，这里截图直观的分析:<br>
main.cc:<br>
![main.cc](./doc/second_allocator.png "main.cc") <br>

demo.cc:<br>
![demo.cc](./doc/malloc.png "demo.cc")<br>

运行时间的对比:<br>
![result](./doc/run_result.png "result")<br>

#STL(SGI)内存池内存的利用
测试代码:<br>
main.cc:<br>
![main.cc](./doc/main.cc2.png)<br>
![res1](./doc/second_allocator_mm.png)<br>
demo.cc:<br>
![demo.cc](./doc/demo.cc2.png)<br>
![res2](./doc/malloc_mm.png)<br>
从图中可以看出，不仅在时间上节省了几秒，<br>
更多的是在内存上节约了有10%

