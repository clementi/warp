# warp

Warp is a command-line warp speed calculator. Because you need one.

<img src="https://vectorified.com/images/star-trek-enterprise-icon-8.png" width="120" height="120">

## Usage

Invoke it thus:

    $ warp 3
    27

You can give it a distance in light-years, which will cause it to give the
travel time in years:

    $ warp 5 -d 4.3
    0.0344

Warp supports both TOS and TNG warp speed scales:

    $ warp 5
    125
    $ warp 5 -t
    213.747

There you go.

## Using with other programs

You can use the output of warp in other programs. For example:

    $ units -qsv1 "`warp 5` c" 'm/s'
    125 c = 3.7474057e+10 m/s

Or this:

    $ units -qsv1 "`warp 5 -t -d 4.3` yr" 'day'
    0.0201172 yr = 7.3476504 day
    
## Installation

Clone the repo and run `make`. (Although the Makefile has `CC` set to 
[`zig cc`](https://ziglang.org/), it's a trivial matter to use GCC or your favorite C compiler 
instead.) Then put warp on your path, and you're ready to go.

[clang]: http://clang.llvm.org/
