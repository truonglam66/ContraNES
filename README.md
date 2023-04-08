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

1. Run scene1/2/3 ---> Chỉnh trong file sample.txt phần [SETTING]
2. Đặt id cho scene1,2,3 txt ---> Chỉnh trong file sample.txt phần [SCENES]
3. Đặt id cho textures (đường dẫn tương đối tới file ảnh) ---> Chỉnh trong file sample.txt phần [TEXTURES]
4. Add 1 object
_Đặt id cho object điền vào file word, excel (để ghi chú không trùng với object khác)
_Tạo 1 file object.txt, ví dụ Bill.txt
_Điền vào file object.txt:
    + Phàn [SPRITES]: id	left	top	right	bottom	texture_id
    + Phần [ANIMATIONS]: ani_id	sprite1_id	time1	sprite2_id	time2...
_Điền vào file scene0X.txt, ví dụ scene01.txt:
    + Phần [ASSETS]: liệt kê tất cả file txt của object, ví dụ Bill.txt
    + Phần [OBJECTS]: type (type 0,1,2,3 được define trong code) x y
_Tạo 1 file .h và .cpp cho object kế thừa từ GameObject, ví dụ CBill.h và CBill.cpp
    + Chỉnh CBill.cpp, hàm Render, define đúng aniId cần Render
_Vào file PlayScene.h khai báo thư viện class mới tạo (CBill.h)
_Vào file PlayScene.cpp, hàm _ParseSection_OBJECTS: define 1 case mới: case OBJECT_TYPE_BILL: obj = new CBill(x, y); break;
