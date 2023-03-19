# ContraNES
SE102
Xây dựng Contra (Nes) gồm các phần Start, Stage 1,2,3,4 và Ending + Credits

Project->Properties->Linker->Input->Addtional Dependencies
d3d10.lib
dxguid.lib
dinput8.lib
%(AdditionalDependencies)

Tools->NuGet Package Manager->Package Manager Console
Install-Package Microsoft.DXSDK.D3DX
