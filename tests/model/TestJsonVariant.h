#include <gtest/gtest.h>
#include "jsonvariant.h"
#include "jsonkeys.h"
#include "testconfig.h"
#include "fileutils.h"
#include <QFile>
#include <QJsonDocument>

//! Test convertion of QVariant from/to QJsonObject.

class TestJsonVariant : public ::testing::Test
{
public:
    TestJsonVariant()
    {
        Utils::create_dir(projectDir());
    }
    ~TestJsonVariant();
    std::string projectDir() const {
        return Testing::TestOutputDir() + "/" + "test_JsonVariant";
    }


    void save_object(const QJsonObject& object, const QString& file_name)
    {
        QFile saveFile(QString::fromStdString(projectDir()) + "/" + file_name);

        if (!saveFile.open(QIODevice::WriteOnly))
            throw std::runtime_error("TestJsonBasics::singleVariant() -> Can't save file");

        QJsonDocument saveDoc(object);
        saveFile.write(saveDoc.toJson());
    }
};

TestJsonVariant::~TestJsonVariant() = default;

//! Invalid QVariant convertion.

TEST_F(TestJsonVariant, invalidVariant)
{
    QVariant variant;

    // from variant to json object
    auto object = json::get_json(variant);
    EXPECT_EQ(object.size(), 2);
    QStringList expected = QStringList() << json::variantTypeKey << json::variantValueKey;
    EXPECT_EQ(object.keys(), expected);
    EXPECT_EQ(object[json::variantTypeKey], json::invalid_type_name);
    EXPECT_TRUE(object[json::variantValueKey].isNull());

    // from json object to variant
    QJsonObject object2{
        {json::variantTypeKey, json::invalid_type_name},
        {json::variantValueKey, QJsonValue()}
    };
    QVariant variant2 = json::get_variant(object2);
    EXPECT_FALSE(variant2.isValid());

    // final comparison
    EXPECT_EQ(variant, variant2);

    // saving to file
    save_object(object, "invalid_variant.json");
}
