/*
    Command line program that acts as a simple calculator.
    It takes a single argument as an expression and prints out the integer result of evaluating it.
    # Author: Eldho Paul
    # Date: Jan-6-2020
    # Version 1.0
*/

#include<stdio.h>
#include<iostream>
#include<vector>

using namespace std;

bool ValidateExpression( int, char*[] );
void ValidationFailed();
bool IsDigitsOnly( int, char*[] );
long Calculate( char, long, long );
bool EvaluateExpressions( int, char*[] );


int main( int argc, char* argv[] )
{
    //Validate the expressions to be calculated
    if( ValidateExpression( argc, argv ))
    {
        //Expression validated
        if( 2 < argc )
        {
            if( !EvaluateExpressions( argc, argv ))
            {
                // Do nothing
                //Calculation failed
            }
        }
    }
    else
    {
        //Expression could not be validated
        ValidationFailed();
    }
}


/*
## ValidateExpression - Function to validate the parameters like proper paranthesis and
##                      number of expressions.
*/
bool ValidateExpression( int nArgNm_i, char* cpArguments_i[] )
{
    // Case of just one command line argument
    if( 2 == nArgNm_i )
    {
        if ( IsDigitsOnly( 1, cpArguments_i ))
        {
            cout << " Numberic Argument-> " << atoi( cpArguments_i[1] ) << "\n";
            return true;
        }
        return false;
    }

    // Checks for functional operations.
    if(( 14 == nArgNm_i) || ( 10 == nArgNm_i) || ( 6 == nArgNm_i))
    {
        if( '(' != *cpArguments_i[ 1 ] ||
             ')' != *cpArguments_i[ nArgNm_i - 1 ])
        {
            cout << " Paranthesis error for the expression \n";
            return false;
        }
        else
        {
            int nOpenbracketNum, nCloseBracketNum;
            nOpenbracketNum = nCloseBracketNum  = 0;

            for( int i = 1; i < nArgNm_i; ++i )
            {
                if( '(' == *cpArguments_i[i] )
                {
                    nOpenbracketNum++;
                }
                else if( ')' == *cpArguments_i[i] )
                {
                    nCloseBracketNum++;
                }
                else if( 0 == strcmp( "add", cpArguments_i[i] ) ||
                         0 == strcmp( "multiply", cpArguments_i[i] ))
                {
                     //Verify operand arguments
                }
                else if( IsDigitsOnly( i, cpArguments_i ))
                {
                    //Validate argument digits
                }
                else
                {
                    // Validation error
                    return false;
                }
            }
            if (nOpenbracketNum != nCloseBracketNum)
            {
                // Validated for open and close brackets.
                return false;
            }
        }
    }
    // Handling invalid argument number
    else
    {
        return false;
    }
    return true;
}


/*
## ValidationFailed - Function to print all the proper input methods on validation fail.
*/
void ValidationFailed()
{
    cout << "Validation failed - Please note the Correct Usage:\n"
        << "1- ( Function Expr Expr) \n"
        << "2- ( Function Expr ( Function Expr Expr ) ) \n"
        << "3- ( Function Expr ( Function Expr ( Function Expr Expr ) ) ) \n"
        << "4- Expr in Digits \n"
        << "Funtion is add/multiply and Expr is any number (32bit) \n\n";
}



/*
## Calculate - Function to calculate the arguments from command line.
*/
long Calculate( char cOperation_i, long nFirstNum_i, long nSecondNum_i )
{
    long nlResult = 0;
    if( '+' == cOperation_i )
    { 
        //Add argumetns
        nlResult = (nFirstNum_i + nSecondNum_i);
    }
    if( '*' == cOperation_i )
    {
        //Multiply arguments
        nlResult = (nFirstNum_i * nSecondNum_i);
    }
    return nlResult;
}


/*
## EvaluateExpressions - Function to assign the opernds and numbers into stacks for final calculation.
*/
bool EvaluateExpressions( int nArgNum_i, char* cArguments_i[] )
{
    auto nExpressionCount = 0;

    vector<long> vNumberstack;
    vector<char> vOperands;
    vNumberstack.clear();
    vOperands.clear();

    for( int i = 1; i < nArgNum_i; ++i )
    {
        if( '(' == *cArguments_i[i] )
        {
            nExpressionCount++;
        }
        else if( ')' == *cArguments_i[i] )
        {
            int nSizeOperand = 0;
            int nSizeNum = 0;
            long lResult = 0;

            nSizeOperand = vOperands.size();

            nSizeNum = vNumberstack.size();
            lResult = Calculate( vOperands[nSizeOperand - 1],
                                 vNumberstack[nSizeNum -1],
                                 vNumberstack[nSizeNum -2]);

            //Pop the calculated operand and numbers
            vOperands.pop_back();
            vNumberstack.pop_back();
            vNumberstack.pop_back();

            //Push the new result into the number stack
            vNumberstack.emplace_back( lResult );
            nExpressionCount--;
            if( 0 == nExpressionCount )
            {
                lResult = vNumberstack[0];
                cout << "Result = " <<lResult;
                return true;
            }                  
        }
        else if( 0 == strcmp( "add", cArguments_i[i] ))
        {
            // Push + sign to operand vector
            vOperands.emplace_back( '+' );
        }
        else if( 0 == strcmp( "multiply", cArguments_i[i] ))
        {
            // Push * sign to operand vector
            vOperands.emplace_back( '*' );
        }
        else if( IsDigitsOnly( i, cArguments_i ))
        {
            // Digits only argument
            vNumberstack.emplace_back(( long )( atoi( cArguments_i[i] )));
        }
    }
    return false;
}


/*
## IsDigitsOnly - Function to validate if an argument is purely numerical.
*/
bool IsDigitsOnly( int nArgNum_i, char* cArray_i[] )
{
    char* cTempArray = cArray_i[nArgNum_i];

    // Print out single expression
    for( int i = 0; i < strlen( cTempArray ); ++i )
    {
        if( isalpha( cTempArray[i] ))
        {
            cout << "Alphabet found in single expression \n";
            return false;
        }
    }
    return true;
}
