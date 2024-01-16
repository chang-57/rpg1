/*#include <SFML/Graphics.hpp>
#include <iostream>
class Button {
public:
    Button(const sf::Vector2f& position, float width, float height, const std::string& label, sf::Font& font, sf::RenderWindow& window)
        : position(position), window(window) {

        // 버튼 생성
        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setPosition(position);
        rectangle.setFillColor(normalColor); // 초기 색상 설정

        // 버튼 레이블 생성
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(position.x + width / 2.0f, position.y + height / 2.0f);

        // 다각형 버튼의 중심 계산
        computeCentroid();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(rectangle);
        window.draw(text);
    }

    bool isMouseOver() {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        return rectangle.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    }

    void update() {
        // 마우스가 버튼 위에 있을 때의 처리
        if (isMouseOver()) {
            rectangle.setFillColor(overColor); // 마우스가 버튼 위에 있으면 색을 바꿈
        }
        else {
            rectangle.setFillColor(normalColor); // 마우스가 버튼 위에 없으면 원래 색으로 복원
        }

        // 다각형 버튼의 텍스트 위치를 다각형의 중심으로 설정
        text.setPosition(centroid);
    }

protected:
    sf::RenderWindow& window;
    sf::RectangleShape rectangle;
    sf::Text text;
    sf::Vector2f position;
    sf::Vector2f centroid; // 다각형 버튼의 중심

    sf::Color normalColor = sf::Color::Blue; // 버튼의 기본 색상
    sf::Color overColor = sf::Color::Green; // 마우스가 버튼 위에 있을 때의 색상

    virtual void computeCentroid() {
        // 가상함수로 선언하여 서브클래스에서 재정의 가능하도록 함
        centroid = position + sf::Vector2f(rectangle.getSize().x / 2.0f, rectangle.getSize().y / 2.0f);
    }
};

class PolygonButton : public Button {
public:
    PolygonButton(const std::vector<sf::Vector2f>& vertices, const std::string& label, sf::Font& font, sf::RenderWindow& window)
        : Button(vertices[0], 0, 0, label, font, window), vertices(vertices) {

        // 다각형 생성
        polygon.setPointCount(vertices.size());

        // 각 꼭지점의 위치 설정
        for (size_t i = 0; i < vertices.size(); ++i) {
            polygon.setPoint(i, vertices[i]);
        }

        polygon.setFillColor(normalColor); // 초기 색상 설정

        // 다각형 버튼의 중심 계산
        computeCentroid();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(polygon);
        Button::draw(window); // 기존 버튼의 draw 함수 호출
    }

    bool isMouseOver() {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        return polygon.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    }

    void update() {
        // 마우스가 버튼 위에 있을 때의 처리
        if (isMouseOver()) {
            polygon.setFillColor(overColor); // 마우스가 버튼 위에 있으면 색을 바꿈
        }
        else {
            polygon.setFillColor(normalColor); // 마우스가 버튼 위에 없으면 원래 색으로 복원
        }
        Button::update(); // 기존 버튼의 update 함수 호출
    }

protected:
    sf::ConvexShape polygon;
    std::vector<sf::Vector2f> vertices;

    void computeCentroid() override {
        // 다각형 버튼의 중심 계산
        centroid = sf::Vector2f(0, 0);
        for (const auto& vertex : vertices) {
            centroid += vertex;
        }
        centroid /= static_cast<float>(vertices.size());
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Polygon Button Example");

    sf::Font font;
    if (!font.loadFromFile("Resources/Fonts/arial.ttf")) {
        return -1;
    }

    // 다각형 버튼 생성
    std::vector<sf::Vector2f> polygonVertices = {
        sf::Vector2f(100, 100),
        sf::Vector2f(200, 100),
        sf::Vector2f(250, 200),
        sf::Vector2f(150, 250)
    };
    PolygonButton polygonButton(polygonVertices, "Click Me", font, window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 버튼 상태 업데이트
        polygonButton.update();

        window.clear();

        // 다각형 버튼 그리기
        polygonButton.draw(window);

        window.display();
    }

    return 0;
}
*/


/*
#include <SFML/Graphics.hpp>
#include <iostream>
int main() {
    sf::RenderWindow window(sf::VideoMode(400, 200), "SFML Button Example");

    sf::RectangleShape button(sf::Vector2f(100, 30));
    button.setFillColor(sf::Color::Green);
    button.setPosition(150, 70);

    sf::Font font;
    if (!font.loadFromFile("Resources/Fonts/arial.ttf")) {
        // 폰트를 로드할 수 없을 경우 처리
        return EXIT_FAILURE;
    }

    sf::Text buttonText("Click me", font, 16);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(170, 75);

    sf::Vector2i prevMousePos;  // 이전 마우스 위치 저장

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    // 버튼이 클릭되면 콘솔에 메시지 출력
                    std::cout << "Button clicked!" << std::endl;
                }
            }
        }

        // 마우스가 움직였을 때만 처리
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (mousePos != prevMousePos) {
            if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                button.setFillColor(sf::Color::Red);
            }
            else {
                button.setFillColor(sf::Color::Green);
            }

            prevMousePos = mousePos;  // 이전 마우스 위치 업데이트
        }

        window.clear();
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }

    return 0;
}
*/

//////////////////////////////////////////////////////////////



/*
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML Point Example");

    sf::Vector2f point(200.0f, 200.0f);

    sf::Clock clock;

    const float targetFPS = 1.0f;
    const sf::Time frameTime = sf::seconds(1.0f / targetFPS);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.getElapsedTime();

        // 경과 시간이 1초가 넘지 않으면 대기
        if (elapsed < frameTime) {
            sf::sleep(frameTime - elapsed);
            elapsed = clock.getElapsedTime();
        }

        window.clear();

        sf::CircleShape pointShape(1.0f);
        pointShape.setFillColor(sf::Color::Red);
        pointShape.setPosition(point);

        window.draw(pointShape);

        window.display();
        clock.restart();
    }

    return 0;
}
*//*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

void countdown(std::atomic<bool>& done) {
    for (int i = 100; i > 0; --i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Countdown: " << i << std::endl;
    }
    done.store(true);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Thread Example");
    
    const int numShapes = 100;
    sf::CircleShape shapes[numShapes];
    sf::VertexArray vertexArray(sf::Triangles, numShapes * 3);

    for (int i = 0; i < numShapes; ++i) {
        shapes[i].setPosition(sf::Vector2f(rand() % 800, rand() % 600));
        shapes[i].setRadius(5.0f);
        shapes[i].setFillColor(sf::Color::Red);

        // 원의 정점을 계산하고 vertexArray에 추가
        for (int j = 0; j < 3; ++j) {
            vertexArray[i * 3 + j].position = shapes[i].getTransform().transformPoint(shapes[i].getPoint(j));
            vertexArray[i * 3 + j].color = shapes[i].getFillColor();
        }
    }

    /// /////////////
    
    std::atomic<bool> done(false);
    std::thread countdownThread(countdown, std::ref(done));
    
    /// /////////////
    sf::Clock clock;

    const float targetFPS = 1.0f;
    const sf::Time frameTime = sf::seconds(1.0f / targetFPS);

    /////////////////

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        sf::Time elapsed = clock.getElapsedTime();

        // 경과 시간이 1초가 넘지 않으면 대기
        if (elapsed < frameTime) {

            sf::sleep(frameTime - elapsed);
            elapsed = clock.getElapsedTime();
        }
        std::cout << "a\n";
        window.clear();

        window.draw(vertexArray);
        window.display();

        // 작업이 끝났으면 창을 닫음
        if (done.load()) {
            window.close();
        }

        clock.restart();

    }

    countdownThread.join(); // 스레드 종료 대기

    return 0;
}
*//*
#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    // 창 생성
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Circles Example");

    // 원의 개수
    const int numCircles = 480000;

    // 원을 그릴 VertexArray
    sf::VertexArray vertexArray(sf::Points, numCircles);

    // 원의 좌표를 계산하여 VertexArray에 추가
    for (int i = 0; i < numCircles; ++i) {
        vertexArray[i].position = sf::Vector2f(i / 600, i % 600);
        vertexArray[i].color = sf::Color::Red;
    }
    // 메인 루프
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // 창 지우기
        window.clear();

        // VertexArray를 그리기
        window.draw(vertexArray);

        // 화면 갱신
        window.display();
        for (int i = 0;i < 480000;i++) {
            vertexArray[i].color = sf::Color::Green;
        }

    }
    return 0;
}*/



/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex myMutex;
// 원을 그릴 VertexArray
// 원 개수
const int numCircles = 480000;
sf::VertexArray vertexArray(sf::Points, numCircles);

void backgroundThreadFunction() {
    sf::Clock threadClock;
    int a;
    while (1) {
        std::cin >> a;
        for (int i = 0;i < 480000;i++)
            vertexArray[i].color = sf::Color::Blue;
    }
    while (1) {
        
    }
    done.store(true);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Thread Example");
    

    // 원의 좌표를 계산하여 VertexArray에 추가
    for (int i = 0; i < numCircles; ++i) {
        vertexArray[i].position = sf::Vector2f(i / 600, i % 600);
        vertexArray[i].color = sf::Color::Red;
    }
    /// /////////////

    std::atomic<bool> done(false);
    std::thread backgroundThread(backgroundThreadFunction);
    /// /////////////
    sf::Clock clock;

    const float targetFPS = 60.0f;
    const sf::Time frameTime = sf::seconds(1.0f / targetFPS);

    /////////////////

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        sf::Time elapsed = clock.getElapsedTime();

        // 경과 시간이 1초가 넘지 않으면 대기
        if (elapsed < frameTime) {
            sf::sleep(frameTime - elapsed);
            elapsed = clock.getElapsedTime();
        }
        window.clear();

        window.draw(vertexArray);
        window.display();

        // 작업이 끝났으면 창을 닫음
        if (done.load()) {
            window.close();
        }

        clock.restart();

    }

    backgroundThread.join(); // 스레드 종료 대기

    return 0;
}
*//*
#include <SFML/Graphics.hpp>
#include <iostream>

const int numCircles = 480000;
sf::VertexArray vertexArray(sf::Points, numCircles);

const std::string vertexShader = R"(
    #version 330 core
    in vec2 position;
    out vec4 color;
    void main() {
        gl_Position = vec4(position, 0.0, 1.0);
        color = vec4(1.0, 0.0, 0.0, 1.0);
    }
)";

const std::string fragmentShader = R"(
    #version 330 core
    in vec4 color;
    out vec4 FragColor;
    void main() {
        FragColor = color;
    }
)";

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shader Example");
    sf::Shader shader;

    if (!shader.loadFromMemory(vertexShader, fragmentShader)) {
        std::cerr << "Failed to load shader!" << std::endl;
        return -1;
    }

    // 원 좌표 계산
    for (int i = 0; i < numCircles; ++i) {
        vertexArray[i].position = sf::Vector2f(i / 600, i % 600);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // GPU에 대량의 원을 그리기
        window.draw(vertexArray, &shader);

        window.display();
    }

    return 0;
}
*//*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <mutex>

bool keyPressed = false;
std::mutex keyPressedMutex;
bool exitThread = false;

void inputFunction() {
    while (!exitThread) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            {
                std::lock_guard<std::mutex> lock(keyPressedMutex);
                keyPressed = true;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

int main() {
    int num = 0;
    const int numPoints = 480000;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Points Example");
    window.setFramerateLimit(60);

    std::thread inputThread(inputFunction);

    sf::VertexArray points(sf::Points, numPoints);

    // 임의의 좌표 및 색상을 가진 점 생성
    for (int i = 0; i < numPoints; ++i) {
        points[i].position = sf::Vector2f(i / 600, i % 600);
        points[i].color = sf::Color::Red;
    }
    for (int i = 600; i < 12800;++i) {
        points[i].color = sf::Color::Blue;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        {
            std::lock_guard<std::mutex> lock(keyPressedMutex);
            if (keyPressed) {
                for (int i = 0; i < numPoints; ++i) {
                    points[i].position.x -= 2;

                    // x 좌표가 화면 왼쪽을 벗어나면 오른쪽 끝으로 이동
                    if (points[i].position.x < 0) {
                        points[i].position.x += window.getSize().x;
                    }
                }
                num++;
                std::cout << num << "\n";
                keyPressed = false;
            }
        }

        window.clear();
        window.draw(points);
        window.display();
    }

    // 종료 플래그 설정 후 스레드 종료 대기
    exitThread = true;
    inputThread.join();

    return 0;
}
*/
/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>

std::mutex mutex;
std::atomic<bool> keyPressed(false);
std::queue<bool> colorChangeQueue;

void inputThreadFunction() {
    while (true) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            std::lock_guard<std::mutex> lock(mutex);
            if (!keyPressed) {
                keyPressed = true;
                colorChangeQueue.push(true);
                std::cout << "A\n";
            }
        }
        else {
            std::lock_guard<std::mutex> lock(mutex);
            if (keyPressed) {
                keyPressed = false;
                colorChangeQueue.push(false);
                std::cout << "B\n";
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    const int numPoints = 480000;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Points Example");
    window.setFramerateLimit(60);

    std::thread inputThread(inputThreadFunction);

    sf::VertexArray points(sf::Points, numPoints);

    // Initialize points with some color
    for (int i = 0; i < numPoints; ++i) {
        points[i].position = sf::Vector2f(i % 800, i / 800);
        points[i].color = sf::Color::Red;
    }
    for (int i = 0;i < 8000;++i) {
        points[i].color = sf::Color::Blue;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        bool isAKeyPressed = false;
        {
            std::lock_guard<std::mutex> lock(mutex);
            isAKeyPressed = keyPressed;
        }

        if (!colorChangeQueue.empty()) {
            bool changeColor = colorChangeQueue.front();
            colorChangeQueue.pop();

            // Change color based on the key press
            for (int i = 0; i < numPoints; ++i) {
                if (i < numPoints - 5600) {
                    points[i].color = points[i + 5600].color;
                }
                else {
                    points[i].color = points[i - 474400].color;
                }
            }
        }

        window.clear();
        window.draw(points);
        window.display();
    }

    inputThread.join(); // Wait for the input thread to finish

    return 0;
}
*/
#include <SFML/Graphics.hpp>
#include <iostream>
int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "RPG Game", sf::Style::Default, settings);

    sf::CircleShape shape(50.0f, 50);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(sf::Vector2f(100, 100));
    shape.setOutlineThickness(10);
    shape.setOutlineColor(sf::Color::Green);

    sf::RectangleShape rectangle(sf::Vector2f(200, 2));
    rectangle.setPosition(sf::Vector2f(300, 100));
    rectangle.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(shape);
        window.draw(rectangle);
        window.display();
    }
}