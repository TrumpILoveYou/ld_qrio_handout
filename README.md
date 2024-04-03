# Architecture Labs: QRIO – Lab1

### 0. Goal

As a beginning "Lab1", we will guide you to get familiar with the running environment of labs in this lecture. You will practice and apply the knowledge about architecture learned from class, using the software emulator [QEMU](https://www.qemu.org/) and profiling tool set [RIO](https://dynamorio.org/).

### 1. Install Docker

We use [Docker](https://www.docker.com/) to provide the running environment of this series of labs. It can be considered as a lightweight virtual machine which is convenient and easy to use. Installers can be downloaded at the home page.

To make sure the Docker is installed successfully, type **docker --version** in the console to check out.

In this series of labs, mastering the use of docker is not required. But in case you need to manipulate the docker images and containers on your own, check out this novel tutorial for the basic use https://www.runoob.com/docker/docker-tutorial.html.

### 2. Setup the environment

First, register a [GITEE](https://gitee.com/) account (let's assume that your username is called "xxx"), and **fork the lab repository (https://gitee.com/wang-hanzhang/qrio_handout.git) to YOUR OWN**.

Second, download project files using git. **Note: please set the file format to LF to avoid script format incompatibility between Windows and Linux, as follows:**

```bash
git config --global core.autocrlf input
# Make sure that you have forked the lab repository to YOUR OWN
#   so that you can submit your own repository link after completing
git clone https://gitee.com/xxx/qrio_handout.git
```

To make things easier, we provide many scripts in folder **cmd** as shortcuts. You don't need to manipulate docker images and containers directly. The scripts whose name ends with **.sh** are used in Linux and Mac OS, and those end with **.bat** are used in Windows. <u>Remember these scripts should be used directly on your machine, not inside the container.</u>

The development environment consists of two components, namely the emulator **QEMU** (in folder qemu-4.1.1) and profiling tools **RIO** (in folder interrio). To build them, <u>enter the directory **cmd**</u> and run the **setup** script (only this script is limited to run in directory **cmd**). This will take about 15 minutes.

The script will build the image and the container both named **qrio** by default, but you can use -i and -c option to configure the name. Note that other scripts in folder **cmd** will refer to container name as **qrio**.

If the **QEMU** is built successfully, the following command will show the manual of **qemu-img**:

```bash
docker exec -it qrio /bin/bash -c "qemu-img --help"
```

If the **RIO** is built successfully, the following command will show the manual of **drrun**:

```bash
docker exec -it qrio /bin/bash -c "~/interrio/build/bin64/drrun --help"
```

**Rememeber that the container should always be turned on!** If it is turned off for reasons like you power off your computer, use
```bash
docker start qrio
```
For more details, see the docker tutorial mentioned in Section 1.

### 3. Run QEMU and RIO

In our labs, QEMU emulates a real ARM64 machine. To run it, first download the kernel and disk images **in the campus network environment** by running **download-image** (in folder **cmd**, the same for scripts mentioned below).

By running **run-qemu**, the QEMU will start and you will see the console of the emulated machine. To exit this console, press the combination of "Ctrl + A" and then press "X".

Inside the machine, the instrumentation tool **qrtag** is provided to do instrumentation on a given program to run. When **qrtag** starts, it hangs to wait another **RIO** process to start profiling work. When **RIO** starts, **qrtag** will continue the program, and provide the instruction trace for **RIO** to do profiling (like instruction counting). An example of how they work will be shown as follows.

First, by typing the following line in the <u>**QEMU** console</u>:

```bash
qrtag -p /home/fib-arm64-static
```

The **qrtag** will start instrumentation on the program "/home/fib-arm64-static". However, the process hangs to wait another **RIO** process to start, so run **run-rio.sh** <u>from another console of your machine</u>. Then, you will see  "/home/fib-arm64-static" continues to run as well. <u>(It's reported that some users will result a segment fault the first time they run **qrtag** with **RIO** together. Don't be panic and simply give an another try.)</u>

As the program in **QEMU** finished, the profile results will be shown in the console of **RIO**. It is the count of branch instructions  (unfinished) during the execution of the program, and it might look like:

```
====== branch counter results ======
643121 total executed instructions
6714 (1.044%) branch instructions
```

### 4. Complete the Instruction Counter

The instruction counter counts the branch instructions during the execution of the program, according to the ARMv8 instruction manual (downloaded at http://10.176.34.8:9090/DDI0487B_a_armv8_arm.pdf). The implementation is in **interrio/clients/drcachesim/tools/opcode_mix.cpp (line 277)**. You will find a switch structure with only one case label named "OP_b". As a result, only **b** instructions are counted.

<u>Your task here, is to find out the rest of the branch instructions in the manual. Add the corresponding branch as case labels like "case OP_xx" for instruction "xx".</u> As you finished your code, remember to compile the **RIO** by running **compile-rio** in **cmd** folders before running. Then, examine your result by profiling the program "/home/fib-arm64-static".

###  5. Benchmark Suite SPEC

[SPEC CPU®](https://www.spec.org/cpu2006/) is a test suite for CPU performance and will be used to simulate application in the real world to test your emulator implemented in following labs. By the following steps, you will compile and learn to build and run SPEC2006 integer benchmark suite.

#### 5.1 Compile SPEC

Enter the container to finish the following task:

```bash
docker exec -it qrio /bin/bash
```

Download and Decompress SPEC:

```bash
cd /root && wget -O assets/cpu2006.tar http://10.176.34.8:9090/cpu2006.tar
cd assets && tar -xvf cpu2006.tar
```
Install SPEC 2006:

```bash
cd cpu2006 && ./install.sh	# press y and enter
```
Finally, compile all the integer benchmark in SPEC. This might take about 5～10 minutes:

```bash
source shrc && runspec -c qrio.cfg int -n 1 -size=test --noreportable
```
Copy all benchmarks into the disk image of QEMU (remember to close the QEMU console first):

```bash
mount ~/assets/disk.img /mnt
cp -r ~/assets/cpu2006/benchspec/CPU2006 /mnt
umount /mnt
```

Enter **QEMU** console by running **run-qemu** (<u>remember to use "exit" to quit the container's console first</u>). You will see the directory "/CPU2006" and benchmarks inside it.

#### 5.2 Run SPEC

For all compiled benchmarks (some benchmarks like 400.perlbench are not compiled), you will find the path **run/run_base_qrio.0000**, with a file **speccmds.cmd** in it. That file tells how to drive the workload of that benchmark. 

Take the **speccmds.cmd** in **401.bzip2** as an example, type in:

```bash
cat /CPU2006/401.bzip2/run/run_base_test_qrio.0000/speccmds.cmd 
```
And you will see 3 lines:

```bash
-C /root/assets/cpu2006/benchspec/CPU2006/401.bzip2/run/run_base_test_qrio.0000
# Ignore this line

-o input.program.out -e input.program.err ../run_base_test_qrio.0000/bzip2_base.qrio input.program 5
-o dryer.jpg.out -e dryer.jpg.err ../run_base_test_qrio.0000/bzip2_base.qrio dryer.jpg 2
# 2 workloads for bzip2, ignore -o/-e options and their arguments
# Binary: bzip2_base.qrio
# Workload 1: input.program 5
# Workload 2: dryer.jpg 2
```

According to **speccmds.cmd**, the commands to run **401.bzip2** are:

```bash
# Go the path
cd /CPU2006/401.bzip2/run/run_base_test_qrio.0000
# Workload 1
./bzip2_base.qrio input.program 5
# Workload 2
./bzip2_base.qrio dryer.jpg 2
```

###  6. Submit

After finishing lab1, please mark your final version using `git tag` as follows:

```bash
git tag -a v1.0 -m "Lab1 finish"
```

(We will take the commit marked by this tag as the source code submission of your lab1)

Your submission should contains these files:
- **Lab report**, which contains:
    - Your lab repository link (formats like https://gitee.com/xxx/qrio_handout.git)
    - Description of the design of your instruction counter
    - Problems encountered during implementation and how you solved them
- **Screenshots** of your final submission running /home/fib-arm64-static and profiling it successfully

Please pack these files into a .zip file and name it "YourStudentID_YourName.zip", then submit it to E-learning.
