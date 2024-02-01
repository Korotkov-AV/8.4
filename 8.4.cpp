// 8.4.cpp :

//зад1:
//нарушен принцип открытости / закрытости кода.так как что бы добавлять новые форматы, например, придется изменять код уже существующей функции saveTo;

//нарушен принцип подстановки Лисков в таких функциях как saveToAsHTMLи др.

//в классе Data нарушен принцип разделения интерефейсов


//зад2 :
#include <map>
#include <string>
#include <iostream>
#include <fstream>


class Data
{
public:
    Data() {};
    Data(std::string data)
        : data_(std::move(data)) {}

    virtual std::string print() {
        return data_;
    };
    virtual void saveTo(std::ofstream& file) {};

    std::string get() const {
        return data_;
    }
protected:
    std::string data_;
};

class HTML : public Data {
public:
    HTML(Data d) {
        data = d.get();
    };

    std::string print() override {
        return "<html>" + data + "<html/>";
    }

protected:
    std::string data;
};

class SaveTo : Data {
public:
    SaveTo(Data* d) : data_(d) {};

    void saveTo(std::ofstream& file) override {
        file << data_->print();
    };
private:
    Data* data_;
};


class Text : public Data {
    Text(Data* d) {
        data = d->get();
    };

    std::string print() override {
        return data;
    }

protected:
    std::string data;
};

class JSON : public Data {
    JSON(Data* d) {
        data = d->get();
    };

    std::string print() override {
        return "{ \"data\": \"" + data + "\"}";
    }

protected:
    std::string data;
};


int main() {
    std::ofstream stream;

    Data myText("is this a solid");
    HTML myHtml(myText);

    std::cout << myHtml.print();

    Data* ptr_html = &myHtml;
    SaveTo mysaving_html(ptr_html);
    mysaving_html.saveTo(stream);
}