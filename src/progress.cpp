#include "progress.h"

#include <iostream>

ProgressBar::ProgressBar(int barWidth)
    : barWidth(barWidth)
{
}

void ProgressBar::Update(double progress)
{
    std::cout << "[";
    
    int position = barWidth * progress;
    
    for (int i = 0; i < barWidth; i++) {
        if (i < position) {
            std::cout << "=";
        } else if (i == position) {
            std::cout << ">";
        } else {
            std::cout << " ";
        }
    }
    
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

void ProgressBar::Done()
{
    std::cout << std::endl;
}
