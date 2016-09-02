# pimenta-judge
A GNU/Linux portable online judge equipped with an ACM ICPC contest system.

## Table of Contents
  * [Installation](#installation)
  * [Usage](#usage)
  * [Directory and file structure](#directory-and-file-structure)
    * [Automatically generated at instance creation](#automatically-generated-at-instance-creation)
    * [Automatically generated during execution](#automatically-generated-during-execution)

## Installation
```bash
$ git clone https://github.com/matheuscscp/pimenta-judge.git
$ cd pimenta-judge
$ make
$ sudo make install
```

## Usage
To create an instance of pjudge, choose a directory name, like `myjudge`, and type:
```bash
$ pjudge install myjudge
```
To start the system, type:
```bash
$ cd myjudge
$ pjudge start
```
Then access [http://localhost:8000/](http://localhost:8000/). To stop, type:
```bash
$ pjudge stop
```

### Hints
* All it takes to run a `pjudge` instance is a directory and a network port, so you can have multiple instances running in the same host!

## Directory and file structure

### Automatically generated at instance creation
| Type      | Name                                      | Function             |
| --------- | ----------------------------------------- | -------------------- |
| Directory | [`database`](#directory-database)         | Database             |
| Directory | [`problems`](#directory-problems)         | Secret test cases    |
| Directory | [`www`](#directory-www)                   | Browser front end    |
| File      | [`httpserver.json`](#file-httpserverjson) | HTTP server settings |

#### Directory `database`

Database files and directories.

#### Directory `problems`
```
problems/
├── 1
│   ├── input
│   │   ├── file1_huge_case
│   │   └── file2
│   └── output
│       ├── file1_huge_case
│       └── file2
└── 2
    ├── input
    │   └── file1
    └── output
        └── file1
```

#### Directory `www`
Files of the web interface, like HTML, CSS and JavaScript. Feel free to modify the web interface of your online judge!

#### File `httpserver.json`
```json
{
  "port": 8000,
  "client_threads": 4,
  "request": {
    "timeout": 5,
    "max_uri_size": 1024,
    "max_header_size": 1024,
    "max_headers": 1024,
    "max_payload_size": 1048576
  },
  "session": {
    "clean_period": 86400
  }
}
```

### Automatically generated during execution
| Type      | Name         | Function                             |
| --------- | ------------ | ------------------------------------ |
| Directory | `attempts`   | All files related to users' attempts |
| File      | `pjudge.bin` | System usage                         |
| File      | `log.txt`    | Log of web session events            |
