import java.util.Scanner;
import java.util.ArrayList;

public class Main
{
    Scanner scan = new Scanner(System.in);
    long startTime;
    long endTime;
    long useTime;
    int firstMatrixM;
    int firstMatrixN;
    int secondMatrixM;
    int secondMatrixN;
    ArrayList<ArrayList<Integer>> firstMatrix = new ArrayList<ArrayList<Integer>>();
    ArrayList<ArrayList<Integer>> secondMatrix = new ArrayList<ArrayList<Integer>>();
    ArrayList<ArrayList<Integer>> resultMatrix = new ArrayList<ArrayList<Integer>>();

    Main()
    {
        System.out.print("Please input M and N of the first matrix.\n");
        if(scan.hasNextInt())
        {
            firstMatrixM = scan.nextInt();
        }
        if(scan.hasNextInt())
        {
            firstMatrixN = scan.nextInt();
        }
        System.out.print("Please input M and N of the second matrix.\n");
        if(scan.hasNextInt())
        {
            secondMatrixM = scan.nextInt();
        }
        if(scan.hasNextInt())
        {
            secondMatrixN = scan.nextInt();
        }

        int temp0 = 0;
        int temp1 = 0;

        System.out.print("Please input the first matrix. End with a blank Line.\n");
        for(temp0 = 0;temp0 < firstMatrixM;temp0++)
        {
            ArrayList<Integer> tempArray = new ArrayList<Integer>();
            for(temp1 = 0;temp1 < firstMatrixN; temp1++)
            {
                if(scan.hasNextInt())
                {
                    tempArray.add(scan.nextInt());
                }
            }
            firstMatrix.add(tempArray);
        }

        System.out.print("Please input the second matrix. End with a blank Line.\n");
        for(temp0 = 0;temp0 < secondMatrixM;temp0++)
        {
            ArrayList<Integer> tempArray = new ArrayList<Integer>();
            for(temp1 = 0;temp1 < secondMatrixN; temp1++)
            {
                if(scan.hasNextInt())
                {
                    tempArray.add(scan.nextInt());
                }
            }
            secondMatrix.add(tempArray);
        }
    }

    private void Calc()
    {
        int temp0 = 0;
        int temp1 = 0;
        int temp2 = 0;
        int temp3 = 0;

        startTime = System.currentTimeMillis();

        for(temp0 = 0;temp0 < firstMatrixM;temp0++)
        {
            ArrayList<Integer> resultTemp = new ArrayList<Integer>();
            for (temp1 = 0;temp1 < secondMatrixN;temp1++)
            {
                for(temp2 = 0; temp2 < firstMatrixN;temp2++)
                {
                    temp3 = temp3+(firstMatrix.get(temp0)).get(temp2)*(secondMatrix.get(temp2)).get(temp1);
                }

                resultTemp.add(temp3);
                temp3=0;
            }
            resultMatrix.add(resultTemp);
        }

        endTime=System.currentTimeMillis();
        useTime=endTime-startTime;
    }

    private void Output()
    {
        int temp0 = 0;
        int temp1 = 0;

        System.out.print("The result matrix after multiplication is:\n");

        for(temp0 = 0;temp0<firstMatrixM; temp0++)
        {
            for (temp1 = 0; temp1 <secondMatrixN; temp1++)
            {
                System.out.print((resultMatrix.get(temp0).get(temp1)));
                if(temp1 == secondMatrixN-1)
                {
                    System.out.print("\n");
                }
                else
                {
                    System.out.print(" ");
                }
            }
        }

        System.out.print("Calculation used " + useTime + " ms.\n");
    }

    public static void main(String[] args)
    {
        Main Start = new Main();
        Start.Calc();
        Start.Output();
    }
}
