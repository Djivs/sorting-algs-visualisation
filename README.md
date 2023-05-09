
# sorting-algs-visualisation
command-line tool to view sorting algorithms visualisation

![](https://github.com/Djivs/sorting-algs-visualisation/blob/master/img/preview.gif)

## Usage
```
General options:  

  -h [ --help ]         Show help. 

  -a [ --alg ] arg      Sorting algorithm to perform. 

  -c [ --count ] arg    Amount of bars to be sorted. 

  -w [ --wait ] arg     Time to wait in microseconds after bar print.
```
  
Example:

<code>./sorting-algs-visualisation -a quick -c 1000 -w 100 </code>

## Available algorithms
- Bubble sort
- Insertion sort
- Selection sort
- Merge sort
- Quick sort
- Stooge sort
- Gnome sort
- Bogo sort

## Dependencies
- gcc
- sfml
- cmake
- boost

## Installation

<code>git clone https://github.com/Djivs/sorting-algs-visualisation.git  
cd sorting-algs-visualisation  
sh build.sh</code>  

## Clean build
<code>sh clean.sh </code>
