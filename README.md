libdynamixel
============

libdynamixel is a C++ interface to the dynamixel actuators. Currently, we have library code and an utility that uses it for a few tasks like changing the IDs, the baudrate and reading angles.

The work is in progress, the documentation too, please be clement.

Compilation and installation
============================
The build system for this library is Waf. Don't run away yet. It has the big advantage of requiring no more than Python installed on your computer. If you run a GNU/Linux OS or Mac OS, you should already have it. Here is how we compile and install it:

1. configuration  
  run `./waf configure` and add `--prefix PATH/TO/INSTALL` if you want to install it to a specific location
2. compilation  
  is as easy as `./waf`
3. installation  
  is simply done with `./waf install`, with the required rights (might need sudo if you install globally)
4. setup the proper authorisation  
  please ensure that you have the proper rights to access the serial interfaces. On GNU/Linux, you might have to add your user to the `dialout` group and log out.

udev rule for USB2AX adapter
============================
If you want your USB2AX serial interface to appear in `/dev` as `usb2axN` (where N is a kernel-attributed integer), you can install the udev rule. It is as simple as moving the `usb2ax.rules` file in this repository to the folder for the udev rules. For ubuntu, it is `/etc/udev/rules.d`.

Using the utility
=================
Since we are right now writing a brand new utility, the user interface is not settled yet and some commands are not implemented. You can still play with the binary `dynamixel2` (the name will change) with the `--help [command]` option to learn how to use it.

> **Caution:** the `get-speed` command gives you the reference speed used in the control loop (if any) and not the current rotational speed of the actuator.

Projects using this library
===========================

Internal projects
-----------------
- omnigrasper_bo_recovery
- [dynamixel_control_hw](https://github.com/resibots/dynamixel_control_hw/)

Other projects
--------------
We would be pleased to hear from you if you use this library in one of your projects.
