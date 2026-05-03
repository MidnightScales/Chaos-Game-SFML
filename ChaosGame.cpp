#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>

using namespace sf;
using namespace std;

enum class GameState { SELECT_SIDES, PLACING_VERTICES, PLACING_START, RUNNING };

int main() {
    RenderWindow window(VideoMode({1200, 800}), "Chaos Game - SFML 3.0");
    window.setFramerateLimit(60);

    Font font;
    if (!font.openFromFile("arial.ttf")) {
        cout << "Error loading arial.ttf!" << endl;
        return -1;
    }

    Text uiText(font); 
    uiText.setCharacterSize(22);
    uiText.setFillColor(Color::White);
    uiText.setPosition({20.f, 20.f});

    GameState state = GameState::SELECT_SIDES;
    int numSides = 3;
    float ratio = 0.5f;
    vector<Vector2f> vertices;
    vector<Vector2f> points;
    Vector2f currentPos;
    int lastVertexIndex = -1;

    srand(static_cast<unsigned>(time(NULL)));

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) window.close();

            // --- KEYBOARD HANDLING ---
            if (event->is<Event::KeyPressed>()) {
                auto key = event->getIf<Event::KeyPressed>()->code;

                // ESCAPE LOGIC
                if (key == Keyboard::Key::Escape) {
                    if (state == GameState::RUNNING) {
                        state = GameState::PLACING_START; // Stop adding points
                    } else {
                        // Reset everything and go back to menu
                        vertices.clear();
                        points.clear();
                        state = GameState::SELECT_SIDES;
                    }
                }

                // MENU SELECTION
                if (state == GameState::SELECT_SIDES) {
                    if (key >= Keyboard::Key::Num3 && key <= Keyboard::Key::Num9) {
                        numSides = (int)key - (int)Keyboard::Key::Num0;
                        state = GameState::PLACING_VERTICES;
                    } else if (key == Keyboard::Key::Num0) {
                        numSides = 10;
                        state = GameState::PLACING_VERTICES;
                    }
                    
                    // Specific Ratios for Extra Credit
                    if (numSides <= 4) ratio = 0.5f;
                    else if (numSides == 5) ratio = 0.618f;
                    else if (numSides == 6) ratio = 0.667f;
                    else if (numSides == 7) ratio = 0.692f;
                    else if (numSides == 8) ratio = 0.707f;
                    else if (numSides == 9) ratio = 0.742f;
                    else if (numSides == 10) ratio = 0.764f;
                }
            }

            // --- MOUSE HANDLING ---
            if (event->is<Event::MouseButtonPressed>()) {
                auto mouse = event->getIf<Event::MouseButtonPressed>();
                if (mouse->button == Mouse::Button::Left) {
                    Vector2f clickPos(static_cast<float>(mouse->position.x), static_cast<float>(mouse->position.y));
                    if (state == GameState::PLACING_VERTICES) {
                        vertices.push_back(clickPos);
                        if (vertices.size() == (size_t)numSides) state = GameState::PLACING_START;
                    } else if (state == GameState::PLACING_START) {
                        currentPos = clickPos;
                        points.clear(); // Clear old points if re-running same vertices
                        points.push_back(currentPos);
                        state = GameState::RUNNING;
                    }
                }
            }
        }

        // --- CALCULATION LOGIC ---
        if (state == GameState::RUNNING) {
            for (int i = 0; i < 250; i++) {
                int randomIndex;
                do { randomIndex = rand() % numSides; } 
                while (numSides >= 4 && randomIndex == lastVertexIndex);
                
                lastVertexIndex = randomIndex;
                currentPos.x += (vertices[randomIndex].x - currentPos.x) * ratio;
                currentPos.y += (vertices[randomIndex].y - currentPos.y) * ratio;
                points.push_back(currentPos);
            }
        }

        // --- UI TEXT ---
        if (state == GameState::SELECT_SIDES) 
            uiText.setString("Chaos Game: Press 3-9 (0 for 10) to start");
        else if (state == GameState::PLACING_VERTICES) 
            uiText.setString("Click to place vertex " + to_string(vertices.size() + 1) + " of " + to_string(numSides));
        else if (state == GameState::PLACING_START) 
            uiText.setString("Click to set start point | Press ESC for Menu");
        else 
            uiText.setString("Running " + to_string(numSides) + "-gon | Esc to Stop | Points: " + to_string(points.size()));

        // --- DRAWING ---
        window.clear();
        window.draw(uiText);
        
        for (const auto& v : vertices) {
            CircleShape vMarker(8.f, numSides);
            vMarker.setFillColor(Color::Yellow);
            vMarker.setOrigin({8.f, 8.f});
            vMarker.setPosition(v);
            window.draw(vMarker);
        }
        for (const auto& p : points) {
            RectangleShape dot({1.f, 1.f});
            dot.setFillColor(Color::Cyan);
            dot.setPosition(p);
            window.draw(dot);
        }
        window.display();
    }
    return 0;
}
