module rrdemo.dotnet.fsharp.main

let quadruple x =
    let double x =
        x * 2

    double(double(x))

let x = quadruple(20)
