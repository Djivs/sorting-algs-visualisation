
# sorting-algs-visualisation
command-line tool to view sorting algorithms visualisation
## Preview video

[![Video preview](img/preview.png)](https://www.youtube.com/watch?v=Bo4JWstlHe4)

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
```
git clone https://github.com/Djivs/sorting-algs-visualisation.git  
cd sorting-algs-visualisation  
sh build.sh
```

## Clean build
<code>sh clean.sh </code>
