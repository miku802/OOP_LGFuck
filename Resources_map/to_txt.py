from PIL import Image

def image_to_array(image_path):
    img = Image.open(image_path)
    #img = img.convert('1')  # 將圖像轉換為黑白模式，將顏色轉換為1位像素值（黑色為1，白色為0）
    pixel_array = []

    for y in range(56):
        row = []
        for x in range(32):
            pixel = img.getpixel((x*10 + 5, y*10 + 5))
            # 黑色的像素為1，白色的像素為0
            print(pixel)
            if pixel[1] > 170:
                row.append(0)
            else:
                row.append(1)
        pixel_array.append(row)

    return pixel_array

# 輸入你的圖像檔案路徑
image_path = "map2.bmp"
result_array = image_to_array(image_path)
for j in range(34):
    print("1 ", end = "")
print()
for i in result_array:
    print("1 ", end = "")
    for j in i:
        print(str(j) + " ", end = "")
    print("1")
for j in range(34):
    print("1 ", end = "")