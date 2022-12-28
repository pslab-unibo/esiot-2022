# Project TestIoT-gradle

Example of IoT REST Web Service - implemented in Java using the Vert.x Framework.

## Setup

Sources are organised as a Gradle project. Before compiling and running the project, the Gradle environment must be set up. In order to run the project the following software/tools must be installed:

* JDK 
* Gradle 
* versions should be aligned (see [Compatibility Matrix](https://docs.gradle.org/current/userguide/compatibility.html))


### Steps for setting up

1. Open a terminal and go inside the TestIoT-gradle directory (inside the ESIOT repo). The content of the directory should be:

	```
├── README.md 
├── app
│   ├── build.gradle
│   └── src
│       └── main
│           ├── java
│           │   └── esiot
│           │       └── module_lab_3_2
│           │           ├── DataPoint.java
│           │           ├── DataService.java
│           │           ├── RunService.java
│           │           ├── TestClient.java
│           │           └── VertxHTTPServerExample.java
│           └── resources
└── settings.gradle
```

All the dependencies of the project are stored in the ```build.gradle``` file.

2. Run gradle init command to initialize the Gradle environment:

	```
	gradle init 
	```
	
3. Run gradle wrapper command to generate wrapper environment:

	```
	gradle wrapper 
	```


## Build/Compiling the project

To compile/build the project, run the wrapper script gradlew specifying the build task:

```
./gradlew build
```

(this is for Linux/Mac/POSIX systems, for Windows system the gradlew.bat script file can be used)


## Running ```RunService```

The ```build.gradle``` file includes the declaration of the main file that is used to run the project (```esiot.module_lab_3_2.RunService```).

To run the service, the wrapper script gradlew can be executed specifying the run task:

```
./gradlew run
```
(this is for Linux/Mac/POSIX systems, for Windows system the gradlew.bat script file can be used)

