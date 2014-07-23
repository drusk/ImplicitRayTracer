#!/bin/sh

ARTICLE=ImplicitSurfacesRayTracer
TEX=$ARTICLE.tex
AUX=$ARTICLE.aux
  
pdflatex $TEX
bibtex $AUX
pdflatex $TEX
pdflatex $TEX
