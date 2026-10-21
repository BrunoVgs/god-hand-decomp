/* sn-2.95.3-136 matched TU. */
typedef unsigned long u64;
typedef unsigned short u16;

typedef struct TextureHeader {
    int unk00;
    int unk04;
    int imageSize;               /* 0x08 */
    unsigned short imageOffset;  /* 0x0C */
    unsigned short unk0E;
    unsigned char unk10[3];      /* 0x10 */
    unsigned char format;        /* 0x13 */
    unsigned short width;        /* 0x14 */
    unsigned short height;       /* 0x16 */
    u64 tex0;                    /* 0x18 */
} TextureHeader;

extern int D_0041EE70[];
int func_00309C30(int format, int width);
void func_0015E510(void *packet, int format, int imageBase, int bufferWidth, u16 width, u16 height, void *image);
void func_0015E8B8(void *packet, int zero, int paletteBase, int one, int w, int h, void *palette);

/* Point a texture's GS state at the packet and emit its sprite data (func_0015E0A0). */
__attribute__((section(".text.func_0015E0A0")))
void func_0015E0A0(void *packet, char *resource, int imageBase, int paletteBase, u64 *tex0)
{
    TextureHeader *header;
    char *image;
    char *palette;
    int format;
    int bufferWidth;
    u64 value;
    unsigned short width, height;

    header = (TextureHeader *)(resource + 0x80);
    if (((unsigned char *)resource)[5] == 0) {
        header = (TextureHeader *)(resource + 0x10);
    }
    format = D_0041EE70[header->format - 1];
    value = (header->tex0 & 0xfffffffffc0fffffUL) | ((u64)(format & 0x3f) << 20);
    header->tex0 = value;
    *tex0 = value;
    width = header->width;
    height = header->height;
    image = (char *)header + header->imageOffset;
    bufferWidth = func_00309C30(format, width);
    *tex0 = (((*tex0 & ~0x3fffUL) | (imageBase & 0x3fff)) & 0xfffffffffff03fffUL) | ((u64)(bufferWidth & 0x3f) << 14) | 0x400000000UL;
    func_0015E510(packet, format, imageBase, bufferWidth, width, height, image);
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
