#ifndef PROGRESS_H
#define	PROGRESS_H

class ProgressBar
{
public:
    /**
     * Creates a progress bar with the bar's width specified in characters.
     */
    ProgressBar(int barWidth = 70);
    
    /**
     * Update progress display.  Progress should be a fraction between
     * 0 and 1.
     */
    virtual void Update(double progress);
    
    /**
     * Mark the process that was being tracked as done.
     */
    virtual void Done();
    
private:
    int barWidth;
};

#endif
