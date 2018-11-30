# Chepp
> [Chest](https://github.com/Karma-IoT/Chest)'s C++ implementation

> Chepp is a radical project. It use the most new standard and support decentralize sources.

## Dependencies

- ninja
- git
- gcc < 7.1 (make)

## Usage



## Commands

### Project commands

#### Initial project

``` shell
$ chepp init
```

The current directory needs to exist `chest.toml`.

#### New file(s)

``` shell
$ chepp new [-t/--type] <pro|h|c|cpp|cls> [-c/--cls] <class>  <path>
```

This subcommand will use the template [-t/--type] and class [-c/--cls] to create file(s) at the specified location.

This subcommand will invoke `${CHEST_SYSROOT}/bin/commands/${type}`. 

#### Build project

``` shell
$ chepp build [-a/--all] [-d/--debug] [-r/-release] [-t/--test] [-e/--example]
```

Build project's specified target.

#### Running target

``` shell
$ chepp run [-e/--example <example name>]
```

If the `-e` flag is set, run the specified example.

#### Test project

``` shell
$ chepp test
```

Execute all test cases.

#### Upload target

``` shell
$ shepp upload [-d/--device <device name>] [-t/--type <debug|release|test|example>] <target name>
```

Upload the specified target to device.

These devices are recorded in the `device`  section in configuration.

#### Remote manage

```shell
$ chepp publish <remote name>
```

`<remote name>` is managed by remote subcommand.

### Global commands

#### Configure

```shell
$ shepp config ls [<section name>]
$ shepp config add <section name>
$ shepp config del <section name> [<key>]
$ shepp config get <section name> <key>
$ shepp config set <section name> <key>=<value>
```

## Environment Variable

- `CHEST_SYSROOT`  the path of source code and binary file. Default value is `~/.chest`.

## Reference

- Chest specification - [https://github.com/Karma-IoT/Chest](https://github.com/Karma-IoT/Chest)

