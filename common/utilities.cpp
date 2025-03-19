#include <sb7.h>
#include "utilities.h"
#include <iostream>
#include <png.h>
bool loadPngImage(const char* name, int& outWidth, int& outHeight, bool& outHasAlpha, GLubyte** outData) {
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE* fp;

    std::cout << "bpaaaa" << std::endl;
    if ((fp = fopen(name, "rb")) == NULL)
        return false;
    std::cout << "bpaaaa1" << std::endl;
    /* Create and initialize the png_struct
     * with the desired error handler
     * functions.  If you want to use the
     * default stderr and longjump method,
     * you can supply NULL for the last
     * three parameters.  We also supply the
     * the compiler header file version, so
     * that we know if the application
     * was compiled with a compatible version
     * of the library.  REQUIRED
     */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
        NULL, NULL, NULL);

    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }
    std::cout << "bpaaaa2" << std::endl;
    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return false;
    }
    std::cout << "bpaaaa3" << std::endl;
    /* Set error handling if you are
     * using the setjmp/longjmp method
     * (this is the normal method of
     * doing things with libpng).
     * REQUIRED unless you  set up
     * your own error handlers in
     * the png_create_read_struct()
     * earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        return false;
    }
    std::cout << "bpaaaa4" << std::endl;

    /* Set up the output control if
     * you are using standard C streams */
    png_init_io(png_ptr, fp);
    std::cout << "bpaaaa5" << std::endl;
    /* If we have already
     * read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);
    std::cout << "bpaaaa51" << std::endl;
    /*
     * If you have enough memory to read
     * in the entire image at once, and
     * you need to specify only
     * transforms that can be controlled
     * with one of the PNG_TRANSFORM_*
     * bits (this presently excludes
     * dithering, filling, setting
     * background, and doing gamma
     * adjustment), then you can read the
     * entire image (including pixels)
     * into the info structure with this
     * call
     *
     * PNG_TRANSFORM_STRIP_16 |
     * PNG_TRANSFORM_PACKING  forces 8 bit
     * PNG_TRANSFORM_EXPAND forces to
     *  expand a palette into RGB
     */
    try
    {
        png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
    }
    catch (...)
    {
        std::cout << "caught" << std::endl;
    }

    std::cout << "bpaaaa6" << std::endl;
    png_uint_32 width, height;
    int bit_depth;
    int t, d = 0;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
        &interlace_type, &t, &d);
    outWidth = width;
    outHeight = height;

    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    *outData = (unsigned char*)malloc(row_bytes * outHeight);
    std::cout << "bpaaaa7" << std::endl;
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    for (int i = 0; i < outHeight; i++) {
        // note that png is ordered top to
        // bottom, but OpenGL expect it bottom to top
        // so the order or swapped
        memcpy(*outData + (row_bytes * (outHeight - 1 - i)), row_pointers[i], row_bytes);
    }
    std::cout << "bpaaaa8" << std::endl;
    /* Clean up after the read,
     * and free any memory allocated */
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    std::cout << "bpaaaa9" << std::endl;
    /* Close the file */
    fclose(fp);
    std::cout << "bpaaaa0" << std::endl;
    /* That's it */
    return true;
}
GLuint GetImageData(const char* filename, int* ptrwidth, int* ptrheight, GLubyte** textureImage) {
    int width, height;
    bool hasAlpha;
    GLuint texture = 0;
    // GLubyte* textureImage;
     //char filename[] = "logo.png";
    std::cout << "bp2222" << std::endl;
    bool success = loadPngImage(filename, width, height, hasAlpha, textureImage);
    std::cout << "bp2222a" << std::endl;
    if (!success) {
        std::cout << "Unable to load png file" << std::endl;
        return texture;
    }
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)*textureImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    //free(textureImage);
    //free(row_pointers);
    //fclose(f);
    *ptrwidth = width;
    *ptrheight = height;
    return texture;

    //std::cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;
}

int texture_load(const char* file, int* width, int* height, GLubyte** textureImage)
{
    std::cout << "bp1111" << std::endl;
    GLuint wintexture = GetImageData(file, width, height, textureImage);
    std::cout << "bp1111a" << std::endl;
    return wintexture;
    //this works in windows but how about android and linux???????????ie can we remove everything after this line??




    //png_structp png_ptr;
    //png_infop info_ptr;
    //unsigned int sig_read = 0;
    //int color_type, interlace_type;
    //FILE* fp;

    //if ((fp = fopen(file, "rb")) == NULL)
    //    return false;

    ///* Create and initialize the png_struct
    // * with the desired error handler
    // * functions.  If you want to use the
    // * default stderr and longjump method,
    // * you can supply NULL for the last
    // * three parameters.  We also supply the
    // * the compiler header file version, so
    // * that we know if the application
    // * was compiled with a compatible version
    // * of the library.  REQUIRED
    // */
    //png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
    //    NULL, NULL, NULL);

    //if (png_ptr == NULL) {
    //    fclose(fp);
    //    return false;
    //}
    ///////////////////////
    FILE* f;//= ptrFile;
    int is_png, bit_depth;
    int color_type;
    int row_bytes;
    unsigned int i = 0;
    png_infop info_ptr, end_info;
    png_uint_32 t_width, t_height;
    png_byte header[8], * image_data;
    png_bytepp row_pointers;
    png_structp png_ptr;
    GLuint texture = 0;
    int alpha;

    if (!(f = fopen(file, "r"))) {
        return -1;
    }
    fread(header, 1, 8, f);
    /* is_png = !png_sig_cmp( header, 0, 8 );
     if ( !is_png ) {
         fclose( f );
         return -1;
     }*/
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
        NULL, NULL);
    if (!png_ptr) {
        fclose(f);
        return -1;
    }
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL,
            (png_infopp)NULL);
        fclose(f);
        return -1;
    }
    end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL,
            (png_infopp)NULL);
        fclose(f);
        return -1;
    }
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(f);
        return -1;
    }
    png_init_io(png_ptr, f);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);
    png_get_IHDR(png_ptr, info_ptr, &t_width, &t_height, &bit_depth,
        &color_type, NULL, NULL, NULL);
    *width = t_width;
    *height = t_height;
    png_read_update_info(png_ptr, info_ptr);
    row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    image_data = (png_bytep)malloc(row_bytes * t_height * sizeof(png_byte));
    if (!image_data) {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(f);
        return -1;
    }
    row_pointers = (png_bytepp)malloc(t_height * sizeof(png_bytep));
    if (!row_pointers) {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        fclose(f);
        return -1;
    }
    for (i = 0; i < t_height; ++i) {
        row_pointers[t_height - 1 - i] = image_data + i * row_bytes;
    }
    png_read_image(png_ptr, row_pointers);
    switch (png_get_color_type(png_ptr, info_ptr)) {
    case PNG_COLOR_TYPE_RGBA:
        alpha = GL_RGBA;
        break;
    case PNG_COLOR_TYPE_RGB:
        alpha = GL_RGB;
        break;
    default:
        printf("Color type %d not supported!\n",
            png_get_color_type(png_ptr, info_ptr));
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return -1;
    }
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t_width, t_height, 0,
        alpha, GL_UNSIGNED_BYTE, (GLvoid*)image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(image_data);
    free(row_pointers);
    fclose(f);
    return texture;
}