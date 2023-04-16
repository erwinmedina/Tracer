# Project 2 - Tracer

## Objective:
Given the following CFG and the parsing table, write a program to trace input strings over the alphabet { i, +, -, *, /, ), ( } and ending with $.

## How To Run:
- Primarily written in C++, and utilizes a build.sh file in order to run.
- Type chmod +x build.sh in the terminal/command prompt, allowing executable permissions.
- Type ./build.sh into the terminal/command prompt to run the program.
- If you're experiencing difficulties, contact me.

## Programmer / Developer
Name | Email
---- | -----
Erwin Medina | erwinmedina@csu.fullerton.edu

## Course Info
Course # | Course Name | Section | Professor
-------- | ----------- | ------- | ---------
CS-323 | Compilers and Languages | 03 | Susmitha Padda

## Results / Screenshots
|                                             |
|:-------------------------------------------:|
|![First String](https://i.imgur.com/oySJeVG.png)|
|![Second String](https://i.imgur.com/DG70NrI.png)|
|![Third String](https://i.imgur.com/F5MWXxH.png)|

## The Good / The Bad
✅ Good! | ❌ Bad :(
------ | -------
Completes objective. | If first value is not found in parsing table than weird error occurs in stack.
Additional examples provides correct output. | Info is a bit hardcoded to fit the parsing table that was provided. Further steps should be taken to make code more flexible.
|| User input has to contain a '$' at the end of string otherwise even if string _CAN_ be traced, it'll say invalid.
|| White space is not handled at all.
