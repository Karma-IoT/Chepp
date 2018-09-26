# Chepp
> [Chest](https://github.com/Karma-IoT/Chest)'s C++ implementation

## Dependencies

- ninja
- git

## Commands

### Project commands

#### Initial project

``` shell
$ chepp init
```

The current directory needs to exist `chest.toml`.

#### New file(s)

``` shell
$ chepp new [-t/--type <pro|h|c|cpp|cls> ] <name>
```

This subcommand will invoke `${CHEST_SYSROOT_BIN}/commands/${type}`. 

`${type}` is `-t`'s value.

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

If the `-e` flag is set, run the specified target.

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

### Global commands

#### Manage remotes

``` shell
$ shepp remote ls
$ shepp remote add <remote name>
$ shepp remote del <remote name>
$ shepp remote attr <remote name> <key>=<value>
```

Remote is the source of `chest`.

Subcommand `ls` will display all remotes.
Subcommand `add` will add new remote.
Subcommand `del` will delete existed remote.
Subcommand `attr` will modify remote's attribute.

#### Refresh index

``` shell
$ shepp refresh
```

Refresh local index.

#### Manage dependencies

``` shell
$ shepp dep update [<chest name>]
$ shepp dep ls
$ shepp dep remove <chest name>
$ shepp dep install <chest name>
```


## Reference

- Chest specification - [https://github.com/Karma-IoT/Chest](https://github.com/Karma-IoT/Chest)

