#include <iostream>
#include <vector>

using namespace std;

#include "iTunes.h"

class Sublist
{
public:
    Sublist(vector<iTunesEntry> *orig = NULL)
        : sum(0), originalObjects(orig) { }
    Sublist addItem(int indexOfItemToAdd);
    void showSublist() const;
    int getSum() const { return sum; }

private:
    int sum;
    vector<iTunesEntry> *originalObjects;
    vector<int> indices;
};

ostream &operator <<(ostream &outputStream, const iTunesEntry &right);
const int &operator +(const int &left, const iTunesEntry &right);






Sublist Sublist::addItem(int indexOfItemToAdd)
{
    Sublist subToAdd = *this;
    subToAdd.indices.push_back(indexOfItemToAdd);
    subToAdd.sum = sum + originalObjects->at(indexOfItemToAdd);
    return subToAdd;
}







void Sublist::showSublist() const
{
    cout << endl << "sum = " << sum << endl << endl;
    cout << "The indices and values that contribute to this sum are:\n\n";
    for (int i = 0; i < indices.size(); i++)
    {
        cout << "Array indice [" << i << "] = ";
        cout << "[" << originalObjects->at(indices[i]) << "]" << endl;
    }
    cout << "                 + ----\n";
    cout << "                   " << sum << endl << endl;
}







int main() {
    const int TARGET = 100000000000;
    vector<iTunesEntry> dataSet;
    vector<Sublist> choices;
    vector<Sublist>::iterator iter, iterBest;
    int k, j, numSets, max, array_size, masterSum;
    bool foundPerfect;

    // read the data
    iTunesEntryReader tunes_input("itunes_file.txt");
    if (tunes_input.readError())
    {
        cout << "couldn't open " << tunes_input.getFileName()
            << " for input.\n";
        exit(1);
    }

    // time the algorithm -------------------------
    clock_t startTime, stopTime;
    startTime = clock();

    // create a vector of objects for our own use:
    array_size = tunes_input.getNumTunes();
    for (int k = 0; k < array_size; k++)
        dataSet.push_back(tunes_input[k]);

    cout << "Target time: " << TARGET << endl;

    //the two for loops below are not a part of the 1.1 algorithm, but
    //instead provide a test case that cautions a user when a target
    //is too great to be met by any combination of values.  It then exits.
    masterSum = 0;
    for (int u = 0; u < dataSet.size(); u++)
    {
        masterSum = masterSum + dataSet[u];
    }

    if (masterSum < TARGET)
    {
        cout << "\nYou can't meet a TARGET this high.";
        cout << "\nThe closest you'll be able to come is: " << masterSum << endl;
        return(1);
    }


    // code provided by student

    foundPerfect = false;
    Sublist S1(&dataSet);
    choices.push_back(S1);

    //the 3.1 algorithm
    for (k = 0; k < dataSet.size(); k++)
    {
        numSets = choices.size();
        for (j = 0; j < numSets; j++)
        {
            if (choices[j].getSum() + dataSet[k] <= TARGET)
                choices.push_back(choices[j].addItem(k));

            if (choices[j].getSum() + dataSet[k] == TARGET)
            {
                foundPerfect = true;
                cout << "\n\nA perfect match was found!\n\n";
                break;
            }
        }
        if (foundPerfect == true)
            break;
    }

    //selects the subset who's sum is closest to the TARGET value
    for (iter = choices.begin(), iterBest = iter; iter != choices.end(); iter++)
    {
        if (iter->getSum() > iterBest->getSum() && iterBest->getSum() <= TARGET)
        {
            iterBest = iter;
        }
    }

    //displays the best qualified sublist
    iterBest->showSublist();

    stopTime = clock();
    cout << "\nAlgorithm Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;

    return 0;
}






//defines the outputStream by the title, followed by artist and duration
//then returns the outputStream
ostream &operator <<(ostream &outputStream, const iTunesEntry &right)
{
    outputStream << right.getTitle() << ", by " << right.getArtist()
        << "(" << right.getTime() << ")";
    return outputStream;
}






//returns the total sum of the int on the left and the int value of the
//time representing the object on the right
const int &operator +(const int &left, const iTunesEntry &right)
{
    int lengthTotal = (left + right.getTime());
    return lengthTotal;
}

/*
//OUTPUT, RUN 1:

Target time: 3600


A perfect match was found!


sum = 3600

The indices and values that contribute to this sum are:

Array indice [0] = [Cowboy Casanova, by Carrie Underwood(236)]
Array indice [1] = [Quitter, by Carrie Underwood(220)]
Array indice [2] = [Russian Roulette, by Rihanna(228)]
Array indice [3] = [Monkey Wrench, by Foo Fighters(230)]
Array indice [4] = [Pretending, by Eric Clapton(283)]
Array indice [5] = [Bad Love, by Eric Clapton(308)]
Array indice [6] = [Everybody's In The Mood, by Howlin' Wolf(178)]
Array indice [7] = [Well That's All Right, by Howlin' Wolf(175)]
Array indice [8] = [Samson and Delilah, by Reverend Gary Davis(216)]
Array indice [9] = [Hot Cha, by Roy Buchanan(208)]
Array indice [10] = [Green Onions, by Roy Buchanan(443)]
Array indice [11] = [I'm Just a Prisoner, by Janiva Magness(230)]
Array indice [12] = [You Were Never Mine, by Janiva Magness(276)]
Array indice [13] = [Hobo Blues, by John Lee Hooker(187)]
Array indice [14] = [I Can't Quit You Baby, by John Lee Hooker(182)]
+ ----
3600


Algorithm Elapsed Time: 14.734 seconds.

Press any key to continue . . .

//RUN 2

Target time: 1234


A perfect match was found!


sum = 1234

The indices and values that contribute to this sum are:

Array indice [0] = [All My Life, by Foo Fighters(263)]
Array indice [1] = [Everybody's In The Mood, by Howlin' Wolf(178)]
Array indice [2] = [Well That's All Right, by Howlin' Wolf(175)]
Array indice [3] = [Samson and Delilah, by Reverend Gary Davis(216)]
Array indice [4] = [Twelve Sticks, by Reverend Gary Davis(194)]
Array indice [5] = [Hot Cha, by Roy Buchanan(208)]
+ ----
1234


Algorithm Elapsed Time: 0.292 seconds.

Press any key to continue . . .

//RUN 3

Target time: 100

sum = 79

The indices and values that contribute to this sum are:

Array indice [0] = [Bullhead's Psalm, by Blue Record(79)]
+ ----
79


Algorithm Elapsed Time: 0.049 seconds.

Press any key to continue . . .

//RUN 4

Target time: 1215752192

You can't meet a TARGET this high.
The closest you'll be able to come is: 22110
Press any key to continue . . .

*/