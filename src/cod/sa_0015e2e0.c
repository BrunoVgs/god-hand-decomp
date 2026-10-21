/* sn-2.95.3-136 matched TU. */
typedef unsigned long u64;
typedef struct TextureHeader {
    char pad00[8];
    int imageSize;
    unsigned short imageOffset;
    char pad0e[5];
    unsigned char format;
    unsigned short width, height;
    u64 tex0;
} TextureHeader;
extern int D_0041EE88[];
extern int func_00309C30(long, int);
extern void func_0015E708(void *, int, long, long, int, long, void *);
extern void func_0015E8B8(void *, long, long, long, int, int, void *);
/* Set texture registers and build the image and palette upload packets. */
__attribute__((section(".text.func_0015E2E0")))
void func_0015E2E0(void *packet, char *resource, int imageBase, int paletteBase, u64 *tex0)
{
    TextureHeader *header;
    char *image;
    int format;
    unsigned short width, height;
    int bufferWidth;
    u64 value;
    char *palette;
    header = (TextureHeader *)(resource + 0x10);
    format = D_0041EE88[header->format - 1];
    value = (header->tex0 & 0xfffffffffc0fffffUL) | ((u64)(format & 0x3f) << 20);
    header->tex0 = value;
    *tex0 = value;
    width = header->width;
    height = header->height;
    image = (char *)header + header->imageOffset;
    bufferWidth = func_00309C30(format, width);
    *tex0 = (((*tex0 & ~0x3fffUL) | (imageBase & 0x3fff)) & 0xfffffffffff03fffUL) | ((u64)(bufferWidth & 0x3f) << 14) | 0x400000000UL;
    func_0015E708(packet, format, imageBase, bufferWidth, width, height, image);
    *tex0 &= 0xff87ffffffffffffUL;
    *tex0 &= 0xff7fffffffffffffUL;
    *tex0 &= 0xe0ffffffffffffffUL;
    *tex0 = (*tex0 & (~0UL >> 3)) | 0x2000000000000000UL;
    *tex0 = (*tex0 & 0xfff8001fffffffffUL) | ((u64)(paletteBase & 0x3fff) << 37);
    palette = (char *)header + header->imageOffset + header->imageSize;
    if (header->format == 5) {
        func_0015E8B8(packet, 0, paletteBase, 1, 16, 16, palette);
        return;
    }
    func_0015E8B8(packet, 0, paletteBase, 1, 8, 2, palette);
}
