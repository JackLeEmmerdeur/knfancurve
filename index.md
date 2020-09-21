Initially meant to be a GUI-frontend [nan0s7/nfancurve](https://github.com/nan0s7/nfancurve), a fan-control shellscript for nvidia cards. That part is by now not implemented as I drifted off to monitoring with graphs and showing basic data about installed cards. I'm using nvidia-smi for that, like nan0s7 does.

The graph part is nearly done and I plan to tackle the fan-control part either by executing the logic of the shell script with Qt process-calls in a long running thread OR just executing the original shell-script, which would probably be faster.

Visit [the github repo](https://github.com/JackLeEmmerdeur/knfancurve) to learn how to build a wip-version
