/***************************************************************************
 * cLogMerge is a program that is designed to take two logfiles and merge  *
 * them together and optionally store the merged files in a third file     *
 *                                                                         *
 * Copyright (C) 2014  Cameron M Brock                                     *
 *                                                                         *
 * This program is free software: you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 *                                                                         *
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
int
main(int argc,char **argv)
    {
    //checking number of command line arguments
    if(argc < 3 || argc > 4)
        {
        //display error message if incorrect number of arguments
        fprintf(stderr,"ERROR: Incorrect number of arguments\n");
        exit(1);
        }
    int size1,size2,size3; 
    Record **log1 = readRecords(argv[1],&size1);
    //read the first record
    Record **log2 = readRecords(argv[2],&size2);
    //read the second record
    size3 = size1 + size2;
    //determine the size of the merged logs
    Record **log3 = mergeRecords(log1,size1,log2,size2);
    //merge the records into one table of records
    if (argc == 4)
        writeTableToFile(argv[3],log3,size3);
        //if there are 4 command line arguments then print the logs to the file
    else
        {
        displayRecordTable(log3,size3);
        printf("# total cost: %f\n",sumOpCost(log3,size3));
        //else write it to stdout
        }
    freeRecord(log1,size1);
    freeRecord(log2,size2);
    free(log3);
    //free the records
    return 0;
    }
