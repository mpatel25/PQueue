#include <iostream>
#include <gtest/gtest.h>
#include "PQueue.h"

#define DURA_TEST 0

/*------------------------ Static Declarations -------------------------------*/

static void copyArray(unsigned array[], unsigned newArray[], unsigned index);
static void swap(unsigned array[], unsigned size);
static void permuteHelper(unsigned array[], unsigned* permutations[],
    unsigned* p_permuteIndex, unsigned at, unsigned size);
static unsigned** permuteArray (unsigned array[], unsigned size);
static void freePermuteArray(unsigned** permutations, unsigned size);
static unsigned factorial (unsigned i);

/*-------------------- Common Functions Definitions --------------------------*/

// The following are helper function to help during testing

// To copy one array into another of the same size
static void copyArray(unsigned array[], unsigned newArray[], unsigned index){
    for (index; index>0; --index)
        newArray[index-1] = array[index-1];
}

// To swap two elements in an array
static void swap(unsigned array[], unsigned a, unsigned b){
    unsigned temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

// Helper function of permuteArray function
static void permuteHelper(unsigned array[], unsigned* permutations[],
    unsigned* p_permuteIndex, unsigned at, unsigned size){
    if (at == (size-1)){
        copyArray(array, permutations[*p_permuteIndex], size);
        ++(*p_permuteIndex);
        return;
    }
    for (unsigned i=at; i<size; ++i){
        swap(array, at, i);
        permuteHelper(array, permutations, p_permuteIndex, (at+1), size);
        swap(array, at, i);
    }
}

// Generates all permutations of an array
// Note: This algo dosen't count for duplicate Elements,
//      therefore repeated permutations
static unsigned** permuteArray (unsigned array[], unsigned size){
    unsigned numPermutations = factorial(size);
    unsigned permuteIndex  = 0;
    unsigned** permutations = new unsigned* [numPermutations];
    for (unsigned i=0; i<numPermutations; ++i){
        permutations[i] = new unsigned [size];
    }
    permuteHelper(array, permutations, &permuteIndex, 0, size);
    return permutations;
}

// To clear the dynamically allocated permutations array
static void freePermuteArray(unsigned** permutations, unsigned size){
    unsigned fact = factorial(size);
    for (unsigned i=0; i<fact; ++i){
        delete[] permutations[i];
    }
    delete[] permutations;
}

// To calculate factorial
static unsigned factorial (unsigned i){
    unsigned fact = 1;
    for (i; i>1; --i) fact *= i;
    return fact;
}

/*------------------------- Common Functions ---------------------------------*/

TEST(CommonFunctionsTest, copyArray_test){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    unsigned testArray[size] = 
        // Test Case
        // Expected Result
        {5, 4, 3, 2, 1};
    unsigned resultArray[size];
    /*-Perform Test---------------------------------------*/
    copyArray(testArray, resultArray, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(testArray[i], resultArray[i]);
}

TEST(CommonFunctionsTest, factorial_test){
    /*-Test Setup-----------------------------------------*/
    const unsigned test_case = 5;
    const unsigned expected = 120;
    unsigned result;
    /*-Perform Test---------------------------------------*/
    result = factorial(test_case);
    /*-Check Results--------------------------------------*/
    ASSERT_EQ(expected, result);
}

TEST(CommonFunctionsTest, permuteArray_test){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 3;
    const unsigned sizeFact = 3*2*1;
    unsigned testArray[size] = 
        // Test Case
        {1, 2, 3};
    const unsigned expectedPermutations[sizeFact][size] =
        // Expected Results
        {
            {1, 2, 3},
            {1, 3, 2},
            {2, 1, 3},
            {2, 3, 1},
            {3, 2, 1},
            {3, 1, 2}
        };
    unsigned** resultPermutations;
    /*-Perform Test---------------------------------------*/
    resultPermutations = permuteArray(testArray, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(expectedPermutations[i][j],
                resultPermutations[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(resultPermutations, size);
}

/*---------------------------- PQueue Testing --------------------------------*/

TEST(PQueueTesting, AllPermutationsOfUniquePriorities_OddSize){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 7;
    const unsigned sizeFact = 7*6*5*4*3*2;
    unsigned testPriorities[size] = 
        // Test Case Priorities
        {1, 2, 3, 4, 5, 6, 7};
    const char expectedOutput[size] =
        // Expected Result
        {'7', '6', '5', '4', '3', '2', '1'};
    unsigned** testPermutations;
    testPermutations = permuteArray(testPriorities, size);
    char resultDequeues[sizeFact][size];    
    PQueue testQ(size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i){
        for(unsigned j=0; j<size; ++j)
            testQ.enqueue('0'+(char)testPermutations[i][j],
                testPermutations[i][j]); 
        for(unsigned j=0; j<size; ++j)
            testQ.dequeue(resultDequeues[i][j]);
    }
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(expectedOutput[j],
                resultDequeues[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(testPermutations, size);
}

TEST(PQueueTesting, AllPermutationsOfUniquePriorities_EvenSize){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 8;
    const unsigned sizeFact = 8*7*6*5*4*3*2;
    unsigned testPriorities[size] = 
        // Test Case Priorities
        {1, 2, 3, 4, 5, 6, 7, 8};
    const char expectedOutput[size] =
        // Expected Result
        {'8', '7', '6', '5', '4', '3', '2', '1'};
    unsigned** testPermutations;
    testPermutations = permuteArray(testPriorities, size);
    char resultDequeues[sizeFact][size];    
    PQueue testQ(size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i){
        for(unsigned j=0; j<size; ++j)
            testQ.enqueue('0'+(char)testPermutations[i][j],
                testPermutations[i][j]); 
        for(unsigned j=0; j<size; ++j)
            testQ.dequeue(resultDequeues[i][j]);
    }
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(expectedOutput[j],
                resultDequeues[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(testPermutations, size);
}

TEST(PQueueTesting, QueueOfSizeTwo){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 2;
    const unsigned sizeFact = 2*1;
    unsigned testPriorities[size] = 
        // Test Case Priorities
        {1, 2};
    const char expectedOutput[size] =
        // Expected Result
        {'2', '1'};
    unsigned** testPermutations;
    testPermutations = permuteArray(testPriorities, size);
    char resultDequeues[sizeFact][size];    
    PQueue testQ(size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i){
        for(unsigned j=0; j<size; ++j)
            testQ.enqueue('0'+(char)testPermutations[i][j],
                testPermutations[i][j]); 
        for(unsigned j=0; j<size; ++j)
            testQ.dequeue(resultDequeues[i][j]);
    }
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(expectedOutput[j],
                resultDequeues[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(testPermutations, size);
}

TEST(PQueueTesting, QueueOfSizeOne){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 1;
    const unsigned sizeFact = 1;
    unsigned testPriorities[size] = 
        // Test Case Priorities
        {1};
    const char expectedOutput[size] =
        // Expected Result
        {'1'};
    unsigned** testPermutations;
    testPermutations = permuteArray(testPriorities, size);
    char resultDequeues[sizeFact][size];    
    PQueue testQ(size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i){
        for(unsigned j=0; j<size; ++j)
            testQ.enqueue('0'+(char)testPermutations[i][j],
                testPermutations[i][j]); 
        for(unsigned j=0; j<size; ++j)
            testQ.dequeue(resultDequeues[i][j]);
    }
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(expectedOutput[j],
                resultDequeues[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(testPermutations, size);
}

TEST(PQueueTesting, FifoEffect_AllSamePriority){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    const unsigned testPriority = 4;
    const char expectedOutput[size] =
        // Expected Result
        {'1', '2', '3', '4', '5'};
    char resultDequeues[size];    
    PQueue testQ(size);
    /*-Perform Test---------------------------------------*/
    for(unsigned i=0; i<size; ++i)
        testQ.enqueue('1'+(char)i, testPriority); 
    for(unsigned i=0; i<size; ++i)
        testQ.dequeue(resultDequeues[i]);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(expectedOutput[i], resultDequeues[i]);;
}

#if DURA_TEST
TEST(PQueueTesting, MaxEnqueueCountWithFifo_DurabilityTest){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 8;
    const unsigned testPriority = 4;
    const char expectedOutput[size] =
        // Expected Result
        {'1', '2', '3', '4', '5', '6', '7', '8'};
    char resultDequeues[size];    
    PQueue testQ(size+1);
    char temp;
    // Number of times to test
    const unsigned numTimes = 0x40000000;
    // Offset enqueueCount from the start
    testQ.enqueue('\0', 0);
    testQ.enqueue('\0', 0);  
    testQ.enqueue('\0', 0);    
    testQ.enqueue('\0', 0);
    // Extra enqueue to not reset enqueueCount
    testQ.enqueue('\0', 0);
    testQ.dequeue(temp);
    testQ.dequeue(temp);
    testQ.dequeue(temp);
    testQ.dequeue(temp);
    /*-Repeat Test----------------------------------------*/
    for(unsigned j=0; j<numTimes; ++j){
        /*-Perform Test-----------------------------------*/
        for(unsigned i=0; i<size; ++i)
            testQ.enqueue('1'+(char)i, testPriority); 
        for(unsigned i=0; i<size; ++i)
            testQ.dequeue(resultDequeues[i]);
        /*-Check Results----------------------------------*/
        for (unsigned i=0; i<size; ++i)
            ASSERT_EQ(expectedOutput[i], resultDequeues[i]);
        /*-Clear Results----------------------------------*/        
        for (unsigned i=0; i<size; ++i)
            resultDequeues[i] = '\0';
    }
}
#endif

TEST(PQueueTesting, HeapOverflow_FifoBehavior){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    const unsigned testPriority = 4;
    const char expectedOutput[size] =
        // Expected Result
        {'1', '2', '3', '4', '5'};
    char resultDequeues[size];    
    PQueue testQ(size);
    // Number of times to test
    const unsigned numTimes = 5;
    /*-Repeat Test----------------------------------------*/
    for (unsigned j=0; j<numTimes; ++j){
        /*-Perform Test-----------------------------------*/
        for(unsigned i=0; i<size; ++i)
            ASSERT_EQ(true, 
                testQ.enqueue('1'+(char)i, testPriority));
        /*-Check Results----------------------------------*/
        for(unsigned i=0; i<size; ++i)
            ASSERT_EQ(false, testQ.enqueue('\0', 0));
        /*-Clear Results----------------------------------*/        
        for(unsigned i=0; i<size; ++i){
            testQ.dequeue(resultDequeues[i]);
            ASSERT_EQ(expectedOutput[i], resultDequeues[i]);
        }
    }
}

TEST(PQueueTesting, HeapUnderflow_FifoBehavior){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    const unsigned testPriority = 4;
    const char expectedOutput[size] =
        // Expected Result
        {'1', '2', '3', '4', '5'};
    char resultDequeues[size]; 
    char temp;   
    PQueue testQ(size);
    // Number of times to test
    const unsigned numTimes = 5;
    /*-Repeat Test----------------------------------------*/
    for (unsigned j=0; j<numTimes; ++j){
        /*-Perform Test-----------------------------------*/
        for(unsigned i=0; i<size; ++i) 
            testQ.enqueue('1'+(char)i, testPriority);
        for(unsigned i=0; i<size; ++i){
            ASSERT_EQ(true, 
                testQ.dequeue(resultDequeues[i]));
            ASSERT_EQ(expectedOutput[i], resultDequeues[i]);
        }
        /*-Check Results----------------------------------*/
        for(unsigned i=0; i<size; ++i){
            temp = '\0';
            ASSERT_EQ(false, testQ.dequeue(temp));
            ASSERT_EQ('\0', temp);
        }
    }
}

TEST(PQueueTesting, HeapOverflow_PriorityBehavior){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    unsigned testPriorities[size] = 
        // Test Case Priorities
        {1, 2, 3, 4, 5};
    const char expectedOutput[size] =
        // Expected Result
        {'5', '4', '3', '2', '1'};
    char resultDequeues[size];    
    PQueue testQ(size);
    // Number of times to test
    const unsigned numTimes = 5;
    /*-Repeat Test----------------------------------------*/
    for (unsigned j=0; j<numTimes; ++j){
        /*-Perform Test-----------------------------------*/
        for(unsigned i=0; i<size; ++i)
            ASSERT_EQ(true, 
                testQ.enqueue('0'+testPriorities[i], 
                testPriorities[i]));
        /*-Check Results----------------------------------*/
        for(unsigned i=0; i<size; ++i)
            ASSERT_EQ(false, testQ.enqueue('\0', 0));
        /*-Clear Results----------------------------------*/        
        for(unsigned i=0; i<size; ++i){
            testQ.dequeue(resultDequeues[i]);
            ASSERT_EQ(expectedOutput[i], resultDequeues[i]);
        }
    }
}

TEST(PQueueTesting, HeapUnderflow_PriorityBehavior){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    unsigned testPriorities[size] = 
        // Test Case Priorities
        {1, 2, 3, 4, 5};
    const char expectedOutput[size] =
        // Expected Result
        {'5', '4', '3', '2', '1'};
    char resultDequeues[size]; 
    char temp;   
    PQueue testQ(size);
    // Number of times to test
    const unsigned numTimes = 5;
    /*-Repeat Test----------------------------------------*/
    for (unsigned j=0; j<numTimes; ++j){
        /*-Perform Test-----------------------------------*/
        for(unsigned i=0; i<size; ++i) 
            testQ.enqueue('0'+testPriorities[i], 
                testPriorities[i]);
        for(unsigned i=0; i<size; ++i){
            ASSERT_EQ(true, 
                testQ.dequeue(resultDequeues[i]));
            ASSERT_EQ(expectedOutput[i], resultDequeues[i]);
        }
        /*-Check Results----------------------------------*/
        for(unsigned i=0; i<size; ++i){
            temp = '\0';
            ASSERT_EQ(false, testQ.dequeue(temp));
            ASSERT_EQ('\0', temp);
        }
    }
}

TEST(PQueueTesting, AllPermutationsOfMixPriorities_EvenSize){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 8;
    const unsigned sizeFact = 8*7*6*5*4*3*2;
    unsigned testPriorities[size] = 
        // Test Case Priorities
        {1, 2, 2, 2, 5, 7, 7, 6};
    unsigned priorityCounts[size] = 
        // Test Case Data
        {0, 0, 0, 0, 0, 0, 0, 0};
    const char expectedOutput[size] =
        // Expected Result
        {'7', 'b', '6', '5', '2', 'b', 'c', '1'};
    unsigned** testPermutations;
    testPermutations = permuteArray(testPriorities, size);
    char resultDequeues[sizeFact][size];    
    PQueue testQ(size);
    unsigned tempPriority;
    char tempChar;
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i){
        for(unsigned j=0; j<size; ++j){
            tempPriority = testPermutations[i][j];
            if (priorityCounts[tempPriority])
                tempChar = 'a' + priorityCounts[tempPriority];
            else tempChar = '0' + tempPriority;
            ++priorityCounts[tempPriority];
            testQ.enqueue(tempChar, tempPriority); 
        }
        for(unsigned j=0; j<size; ++j)
            testQ.dequeue(resultDequeues[i][j]);
        for(unsigned j=0; j<size; ++j)
            priorityCounts[j] = 0;
    }
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(expectedOutput[j],
                resultDequeues[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(testPermutations, size);
}


/*-------------------------------- MAIN --------------------------------------*/

int main (int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*--------------------------------- END --------------------------------------*/
