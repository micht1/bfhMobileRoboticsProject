<a href="https://www.bfh.ch/de/studium/bachelor/mikro-medizintechnik/" target="blank">
<img src="https://www.bfh.ch/dam/jcr:63dbff1d-5056-4168-b6ce-acfdf8415ef8/Logo%20BFH.svg" alt="BFH" width="80"/>
</a>

# Robotics 2 – Mobile Robotics
Prof. Dr. Gabriel Gruener
## Robotics Project with Yellow

### Purpose
  * This repository contains all the information related to the Robotics 2 – Mobile Robotics project.
  * The repository is also used to store your __project group data__ (e.g. project documentation and software)

### Contents
#### [1. Documentation](Documentation/README.md)  
This directory contains all the mechanical and electronic documentation.

**ATTENTION**: When charging Yellow's batteries, make sure the charger has the right configuration. Refer to the [Hardware Documentation](Documentation/README.md).

#### [2. Exercises](Exercises/README.md)
This directory contains the exercise descriptions as well as the final project task description.

#### [3. Software](Software)  
This directory contains the robot's on-board software.

In here you will also find a [manual on how to compile and mount](Software/README.md) your program as well as a [manual on how to configure the QtCreator IDE](Software/QtCreator-projectConfiguration-Windows.md) for editing the source code and compile and mount it inside this IDE.

#### [4. Remote](Remote)  
This directory contains all files related to remote communication to the robot from your PC. Refer to the [Remote/README.md](Remote/README.md) file for more information.

### Repository updates
To update your repository to the current project milestone, you need to fetch the newest data from the template repository.
To do this, execute the following commands in a terminal (linux terminal, windows git bash or other git GUI), where `XX` stands for the last 2 digits of the current year (e.g. 19 for 2019) and `groupNumber` stands for your group number (e.g. 01):

```bash
.../project-XX_groupNumber$ git fetch upstream
.../project-XX_groupNumber$ git merge upstream/master
.../project-XX_groupNumber$ git push
```

If the `upstream` repository was not set before, you need to define it (one-time command). This sets a new remote called _upstream_ with the ssh-URL of the template repository:

```bash
.../project-XX_groupNumber$ git remote add upstream git@gitlab.ti.bfh.ch:roboticsLab/Education/BTF6420/project-XX-template.git
```

You can always display your remote repositories using:

```bash
.../project-XX_groupNumber$ git remote -v
```

---

##### Author
  * Iris Näf <irislisa.naef@bfh.ch>
  * Gabriel Gruener <gabriel.gruener@bfh.ch>

##### Resources
  * Robotics 2 – Mobile Robotics course by G. Gruener

##### Prerequisites
  * Git​ Bash or other terminal with `git`
