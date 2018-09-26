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

This subcommand will invoke `${CHEST_SYSROOT_BIN}/commands/${type}`. `${type}` is `-t`'s value.

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

### Global commands

## Reference

- Chest specification - [https://github.com/Karma-IoT/Chest](https://github.com/Karma-IoT/Chest)

