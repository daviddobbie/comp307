import java.util.*;
import java.io.*;

/**
 * Implementation of the k-Nearest Neighbour algorithm. Used to classify the iris data set given.
 * COMP307 Assignment 1 - Part 1
 * David Dobbie - 300340161
 */
public class NearestNeighbour {





    public static void main(String [ ] args)
    {
        String error ="";

        if(args.length != 2){
            error = "Need 2 file arguments";
            System.out.println(error);
            return;
        }

        
		System.out.println(args.length);
        new NearestNeighbour();  
    }


}
