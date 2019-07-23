# Chepp
> [Chest](https://github.com/Karma-IoT/Chest)'s C++ implementation

> Chepp is a radical project. It uses the newest standard and support decentralize sources.

## Dependencies

- ninja
- git
- gcc > 7.1 (make)

## Commands

### Project related commands

#### New file(s)

```shell
$ chepp new [-t/--type <type>] [-c/-class <class>] [-l/--list] <name>
```

- `-t/--type` : type of new file, this command will invoke `${CHEST_SYSROOT}/bin/.chest/commands/<type>`, and then pass all arguments.
- `-c/--class` : class of new file.
- `-l/--list` : list all template for `<type>` or all.
- 

#### Initial project

``` shell
$ chepp init
```

The current directory must exist `chest.toml`.

#### Publish project

``` shell
$ chepp publish <remote name>
```

`<remote name>` is managed by remote subcommand.

#### Build project

``` shell
$ chepp build [-a/--all] [-d/--debug] [-r/-release] [-t/--test] [-e/--example]
```

Build project's specified target

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

### Global commands

#### Configure

```shell
$ shepp config ls [<section name>]
$ shepp config add <section name>
$ shepp config del <section name> [<key>]
$ shepp config get <section name> <key>
$ shepp config set <section name> <key>=<value>
```


## Reference

- Chest specification - [https://github.com/Karma-IoT/Chest](https://github.com/Karma-IoT/Chest)

