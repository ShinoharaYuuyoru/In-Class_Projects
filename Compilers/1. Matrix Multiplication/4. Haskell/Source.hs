import Data.List
import Data.Time
import Data.Time.Clock.POSIX

startTime = 0.0
endTime = 0.0
tempStrInput = []
tempLine = []
firstMatrixM = 0
firstMatrixN = 0
secondMatrixM = 0
secondMatrixN = 0

firstMatrix = []
secondMatrix = []
resultMatrix = []

--Change String to some integers
strtoInt :: String -> [Int]
strtoInt = map read . words

--MatrixInput(String)
matrixInput :: IO [String]
matrixInput = do
	tempStrInput <- getLine
	if tempStrInput == ""
		then return []
	else do
		tSIs <- matrixInput
		return (tempStrInput:tSIs)

--BuildMatrix
buildMatrix :: [String] -> [[Int]] -> [[Int]]
buildMatrix [] ans = reverse ans
buildMatrix (l:ls) ans = buildMatrix ls ((strtoInt l) : ans)

--Multiplication
mmult :: [[Int]] -> [[Int]] -> [[Int]] 
mmult a b = [ [ sum $ zipWith (*) ar bc | bc <- (transpose b) ] | ar <- a ]

--Format
format :: String -> [[String]] -> String
format separater = intercalate "\n" . map (intercalate separater)

--Change Matrix to String
output :: [[Int]] -> String
output = format " " . (map . map) show

main = do
	print "Please input M and N of the first matrix."
	tempStrInput <- getLine
	let tempLine = strtoInt tempStrInput
	let firstMatrixM = tempLine !! 0
	let firstMatrixN = tempLine !! 1
	print "Please input M and N of the second matrix."
	tempStrInput <- getLine
	let tempLine = strtoInt tempStrInput
	let secondMatrixM = tempLine !! 0
	let secondMatrixN = tempLine !! 1
	
	print "Please input the first matrix. End with a blank Line."
	tempStrInput <- matrixInput
	let firstMatrix = buildMatrix tempStrInput []
	print "Please input the second matrix. End with a blank Line."
	tempStrInput <- matrixInput
	let secondMatrix = buildMatrix tempStrInput []
	
	startTime <- getPOSIXTime
	let resultMatrix = firstMatrix `mmult` secondMatrix
	
	let resultString = output resultMatrix
	putStrLn resultString
	endTime <- getPOSIXTime
	putStr "Calculation used "
	print (endTime - startTime)
	