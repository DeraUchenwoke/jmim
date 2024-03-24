# Joint Mutual Information Maximimisation (JMIM) CLI Application 
## A bit of context
This repository follows after my final year project. The aim of the project was to reduce the memory consumption of a [LightGBM](https://github.com/microsoft/LightGBM) model used for malware detection. To accomplish this, I used the Joint Mutual Information Maximisation (JMIM) algorithm to select the $K$ most 'important' variables to train the model on. Given there was no public JMIM pre-built package at the time, the algorithm was [written in Python from scratch](https://www.kaggle.com/code/deera25555/jmim-lgbm#JMIM). 

### The Problem
My original implementation has the following issues: 
1. Not language agnostic i.e., only suitable for Python programs.
2. Adopts a slow, naive approach to handle discrete and continuous variables.

### The Solution

The purpose of this repository is to use JMIM to create a tool which selects the $K$ most 'important' variables via CLI given a CSV file of discrete/continuous random variables.

## A dash of mathematics
For those interested to know how the algorithm above was derived go to section *3.4.1* of my final year project [paper](./final_project.pdf).

## Installation

### Prerequisites
This program requires: 
- cmake (At least version 3.8)

For Windows users:
1. Clone the repository: `git clone https://github.com/DeraUchenwoke/jmim.git`
2. In PowerShell terminal run: `cd scripts` followed by `.\setup.ps1`.

## Usage 

### Examples

## Style guide & practices
[Google style guide](https://google.github.io/styleguide/cppguide.html#The__define_Guard).
[Powershell practice and style](https://github.com/PoshCode/PowerShellPracticeAndStyle/blob/master/Style-Guide/Code-Layout-and-Formatting.md).

The tool was written in line with [CPP core guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#main).