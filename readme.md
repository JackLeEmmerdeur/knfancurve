# KNFanCurve

Initially meant to be a GUI-frontend [nan0s7/nfancurve](https://github.com/nan0s7/nfancurve), a fan-control shellscript for nvidia cards. That part is by now not implemented as I drifted off to monitoring with graphs and showing basic data about installed cards. I'm using nvidia-smi for that, like nan0s7 does.

The graph part is nearly done and I plan to tackle the fan-control part either by executing the logic of the shell script with Qt process-calls in a long running thread OR just executing the original shell-script, which would probably be faster.

Visit the [github page](https://jackleemmerdeur.github.io/knfancurve/) for additional info.

<br>

## Build

### With QtCreator

If you got QtCreator development already set up you can spare yourself the below instructions and just open the .pro file in QtCreator and build the application.

### Docker

Included is a dockerfile that builds a moderate sized (about 1gig) debian:buster-slim image with just the base cmake and Qt5 build environment. 

#### Step 1

##### 1.1 Change to the cloned project folder
`cd /home/USER/projects/knfancurve`

##### 1.2 Create a build folder
##### either in parent-folder of the project folder...
`mkdir ../linuxbuild`

##### 1.3 or in source folder... 
`mkdir linuxbuild`


#### Step 2

##### Edit the volumes in docker-compose.yml

Example:

```
volumes:
   - ../linuxbuild:/docker/build
   - .:/docker/src

```

This volumes-declaration

1. Maps the parent build-folder `linuxbuild` you created
in step 1.2 above to the container folder `/docker/build`
2. Maps the current directory (step 1.1), the sourcefolder,
to the container folder `/docker/src`    

#### Step 3
Inside the your cloned project dir run
`docker-compose up`

This will:
* pull the docker-image debian:buster-slim 
* install qt5 and qt5-libaries
* install gcc and cmake-build-system 
* build the knfancurve binary in `linuxbuild`

Everytime you want to build in future just call `docker-compose up` and have a fresh build in 5 seconds!
 
<br>

### To do (without priorities):

* CSV logging needs regular memory purge. Better solution: SQLite or redis  
* Read muuuuch more infos from card within configuration-tab card-infos
* Seperate card-info into new tab
* Graph grid cell-resizing not working right
* Add nfancurve-shell-script options to configuration
* Clone latest nfancurve-shell-script to config-dir of application
