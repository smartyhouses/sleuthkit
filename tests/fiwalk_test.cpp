/*
 * fiwalk_test.cpp
 *
 *  2024-09-29 - slg - modified to read from TEST_IMAGES the paths for the disk images
 *  2024-09-12 - slg - created
 *
 */

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <string>

#include "tools/fiwalk/src/fiwalk.h"

void check_image(std::string img_path, std::string dfxml2_path) {
    CAPTURE(img_path);
    INFO("test: fiwalk " << img_path)

    /* the output XML file should be the XML file with a 2 added.
     * If there is no XML file, then add ".xml2" to the image file.
     */
    if (dfxml2_path.empty()) {
      dfxml2_path = img_path + ".xml2";
    }
    else {
      dfxml2_path += "2";
    }

    const int argc = 1;
    char* const argv[] = { &img_path[0], nullptr };

    if (access(argv[0], F_OK) == 0){
        fiwalk o;
        o.filename = argv[0];
        o.argc = argc;
        o.argv = argv;
        o.opt_variable = false;
        o.opt_zap = true;
        o.xml_fn = dfxml2_path;
        o.run();
        CHECK(o.file_count > 0);
        SUCCEED(img_path << " file count = " << o.file_count);
    }
    else {
        FAIL(img_path << " not found");
    }
    /* XML files are checked by the python driver */
}

#ifdef HAVE_LIBEWF
TEST_CASE("test_disk_images imageformat_mmls_1.E01", "[fiwalk]") {
    check_image(
      "tests/from_brian/imageformat_mmls_1.E01",
      "tests/from_brian/imageformat_mmls_1.E01.xml"
    );
}
#endif

TEST_CASE("test_disk_images ntfs-img-kw-1.dd", "[fiwalk]") {
    check_image(
      "tests/from_brian/ntfs-img-kw-1.dd",
      "tests/from_brian/3-kwsrch-ntfs.xml"
    );
}

TEST_CASE("test_disk_images ext3-img-kw-1.dd", "[fiwalk]") {
    check_image(
      "tests/from_brian/ext3-img-kw-1.dd",
      ""
    );
}

TEST_CASE("test_disk_images daylight.dd", "[fiwalk]") {
    check_image(
      "tests/from_brian/daylight.dd",
      ""
    );
}

TEST_CASE("test_disk_images image.gen1.dmg", "[fiwalk]") {
    check_image(
      "tests/from_brian/image.gen1.dmg",
      ""
    );
}

TEST_CASE("test_disk_images image.dd", "[fiwalk]") {
    check_image(
      "tests/from_brian/image.dd",
      "tests/from_brian/image_dd.xml"
    );
}
