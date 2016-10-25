@echo off
SET inPath=in
SET resultPath=result
SET outPath=out
echo.--
GOL.exe --load %inPath%/random250_in.gol --generations 250 --save %resultPath%/random250_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random250_result.gol" "%outPath%/random250_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random500_in.gol --generations 250 --save %resultPath%/random500_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random500_result.gol" "%outPath%/random500_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random750_in.gol --generations 250 --save %resultPath%/random750_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random750_result.gol" "%outPath%/random750_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random1000_in.gol --generations 250 --save %resultPath%/random1000_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random1000_result.gol" "%outPath%/random1000_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random1250_in.gol --generations 250 --save %resultPath%/random1250_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random1250_result.gol" "%outPath%/random1250_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random1500_in.gol --generations 250 --save %resultPath%/random1500_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random1500_result.gol" "%outPath%/random1500_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random1750_in.gol --generations 250 --save %resultPath%/random1750_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random1750_result.gol" "%outPath%/random1750_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random2000_in.gol --generations 250 --save %resultPath%/random2000_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random2000_result.gol" "%outPath%/random2000_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random3000_in.gol --generations 250 --save %resultPath%/random3000_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random3000_result.gol" "%outPath%/random3000_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random4000_in.gol --generations 250 --save %resultPath%/random4000_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random4000_result.gol" "%outPath%/random4000_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random5000_in.gol --generations 250 --save %resultPath%/random5000_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random5000_result.gol" "%outPath%/random5000_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random6000_in.gol --generations 250 --save %resultPath%/random6000_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random6000_result.gol" "%outPath%/random6000_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random7000_in.gol --generations 250 --save %resultPath%/random7000_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random7000_result.gol" "%outPath%/random7000_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random8000_in.gol --generations 250 --save %resultPath%/random8000_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random8000_result.gol" "%outPath%/random8000_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random9000_in.gol --generations 250 --save %resultPath%/random9000_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random9000_result.gol" "%outPath%/random9000_out.gol" /L
echo.
echo.--
GOL.exe --load %inPath%/random10000_in.gol --generations 250 --save %resultPath%/random10000_result.gol --measure
echo.
echo.n|Comp "%resultPath%/random10000_result.gol" "%outPath%/random10000_out.gol" /L
echo.
pause