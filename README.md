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
### Parsing Table:
<table>
  <tr>
    <th>States</th>
    <th>a</th>
    <th>+</th>
    <th>-</th>
    <th>*</th>
    <th>/</th>
    <th>(</th>
    <th>)</th>
    <th>$</th>
  </tr>
  <tr>
    <th>E</th>
    <td>TQ</td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td>TQ</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <th>Q</th>
    <td></td>
    <td>+TQ</td>
    <td>-TQ</td>
    <td></td>
    <td></td>
    <td></td>
    <td>ɛ</td>
    <td>ɛ</td>
  </tr>
  <tr>
    <th>T</th>
    <td>FR</td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td>FR</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <th>R</th>
    <td></td>
    <td>ɛ</td>
    <td>ɛ</td>
    <td>*FR</td>
    <td>/FR</td>
    <td></td>
    <td>ɛ</td>
    <td>ɛ</td>
  </tr>
  <tr>
    <th>F</th>
    <td>a</td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td>(E)</td>
    <td></td>
    <td></td>
  </tr>
</table>

| (a+a)*$ | ![First String](https://i.imgur.com/bLOgTVp.png)
| --------- | ------ |
| a*(a/a)$ | ![Second String](https://i.imgur.com/oY4EBjp.png)
| a(a+a)$ | ![Third String](https://i.imgur.com/auC7JVS.png)

## The Good / The Bad
✅ Good! | ❌ Bad :(
------ | -------
Completes objective. | If first value is not found in parsing table than weird error occurs in stack.
Additional examples provides correct output. | Info is a bit hardcoded to fit the parsing table that was provided. Further steps should be taken to make code more flexible.
|| User input has to contain a '$' at the end of string otherwise even if string _CAN_ be traced, it'll say invalid.
|| White space is not handled at all.
