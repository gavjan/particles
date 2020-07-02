# Particles
## Description
The goal of the task is to write a program describing the behavior of a particle in some imaginary quantum world.

A particle is designated by a string made from any combination of the numbers {0,1,2,3}.

Just like particles a quantum history is also designated by a string of numbers {0,1,2,3}, however a quantum history
includes all particles that are its prefix (ex. the history `0123` includes particles `0`, `01`, `012` and `0123`)

Each declared particle can have energy value assigned to it
The energies of two declared particles can be equated, which means that a change in energy for one of these particles
also causes a change in the energy of the other.

The energy equation relationship attributed to histories is equivalence.

## Implementation

After starting the program, no quantum histories are declared, so no particle is assigned energy and no two particles are equated.

Then, the program accepts the following commands:

-   `DECLARE history`- declares every particle that is a prefix of `history`.

-   `REMOVE history`- removes every particle that starts with `history`.

-   `VALID particle` - Checks if `particle` given is declared.

-   `ENERGY particle energy`- If `particle` is declared has no energy assigned to it, assigns `energy` to it (overwrites existing energy).

-   `ENERGY particle`- If `particle` is declared and has energy assigned, prints that energy.

-   `EQUAL particle_a particle_b`- If `particle_a`and `particle_b` were declared, then:
    - (a) if at least one of the particles has energy assigned, balances their energies and closes the equivalence relationship.
    - (b) if both particles have energy assigned to them, then assigns the arithmetic average of these energies to both of them (with rounding down if necessary).
    - (c) if both particles are identical or already have equal energies, doesn't change anything.

## Information printed by the program

After a correct execution of a command, the program writes:

-   `OK` for every recognized command except `VALID` and a single parameter version of `ENERGY`.
-   `YES`or `NO`depending on the result of the command `VALID`.
-   `integer` that is the energy value for the single parameter command `ENERGY`.
-   `ERROR` to `stderr` for each incorrect line of command.

## Examples

Example tests for the program can be found in the folder `tests`.

## Compile

compile and run executable `particles`:
```shell script
make run
```

run with valgrind:
```shell script
make valgrind
```

check against the tests located in the folder `tests`:
```shell script
make test
```


## Tests
Tests can be found [here](https://github.com/gavjan/particles/releases/tag/tests)


