# Opis implementacji brakujących elementów do gry Breakout

## 1. Warunki końca gry

- **Przegrana**: Jeśli piłka spadnie poniżej dolnej krawędzi ekranu, kończymy grę.

  ```cpp
  if (ball.position.y > SCREEN_HEIGHT) {
      running = false;
      std::cout << "Game Over!" << std::endl;
  }
  ```

- **Wygrana**: Jeśli wszystkie cegły zostaną zbite, gracz wygrywa.

  ```cpp
  if (bricks.empty()) {
      running = false;
      std::cout << "You Win!" << std::endl;
  }
  ```

## 2. Wyświetlanie wyniku

- **Inicjalizacja czcionki** (dodaj do inicjalizacji SDL3_TTF):

  ```cpp
  TTF_Font* font = TTF_OpenFont("path/to/font.ttf", 24);
  ```

- **Konwersja wyniku do tekstu**:

  ```cpp
  std::string scoreText = "Score: " + std::to_string(score);
  ```

- **Renderowanie tekstu**:

  ```cpp
  SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), {255, 255, 255});
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  ```

- **Wyświetlanie tekstu**:

  ```cpp
  SDL_Rect scoreRect = {10, 10, 100, 30};
  SDL_RenderTexture(renderer, texture, NULL, &scoreRect);
  ```

## 3. Zmiana prędkości piłki

- **Zwiększanie prędkości po odbiciu**:
  ```cpp
  ball.velocity.x *= 1.05;
  ball.velocity.y *= 1.05;
  ```

## 4. Zmiana kolorów cegieł w zależności od wytrzymałości

- **Przypisanie koloru do wytrzymałości**:
  ```cpp
  SDL_Color brickColors[] = {{255, 0, 0}, {255, 165, 0}, {255, 255, 0}};
  SDL_Color color = brickColors[brick.health - 1];
  ```

## 5. Efekty wizualne po zbiciu cegły

- **Dodanie efektu migotania**:
  ```cpp
  for (int i = 0; i < 3; ++i) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderFillRect(renderer, &brick.rect);
      SDL_RenderPresent(renderer);
      SDL_Delay(50);
  }
  ```

## 6. Dodanie prostego systemu poziomów

- **Przejście na nowy poziom**:
  ```cpp
  if (bricks.empty()) {
      level++;
      loadLevel(level);
  }
  ```

## 7. Restart gry po przegranej lub wygranej

- **Resetowanie gry**:

  ```cpp
  void resetGame() {
      ball.position = {400, 300};
      ball.velocity = {200, -200};
      bricks = generateBricks();
      score = 0;
  }
  ```

- **Sprawdzenie warunków i restart**:

  ```cpp
  if (!running) {
      resetGame();
      running = true;
  }
  ```

## 8. Dodanie bonusów

- **Struktura bonusów**:

  ```cpp
  struct Bonus {
      SDL_FRect position;
      SDL_FPoint velocity;
      int type; // 0 - dodatkowe życie, 1 - większa paletka, 2 - szybsza piłka
  };
  ```

- **Generowanie bonusu po zniszczeniu cegły**:

  ```cpp
  if (rand() % 5 == 0) {
      bonuses.push_back({brick.position, {0, 100}, rand() % 3});
  }
  ```

- **Ruch bonusów**:

  ```cpp
  for (auto& bonus : bonuses) {
      bonus.position.y += bonus.velocity.y * deltaTime;
  }
  ```

- **Kolizja bonusu z paletką**:

  ```cpp
  for (auto it = bonuses.begin(); it != bonuses.end(); ) {
      if (SDL_HasIntersectionF(&it->position, &paddle.rect)) {
          applyBonus(it->type);
          it = bonuses.erase(it);
      } else {
          ++it;
      }
  }
  ```

## 9. Dodanie twardych cegieł

- **Nowa struktura cegieł**:

  ```cpp
  struct Brick {
      SDL_FRect rect;
      int health;
      bool indestructible;
  };
  ```

- **Tworzenie twardych cegieł**:

  ```cpp
  if (rand() % 10 == 0) {
      bricks.push_back({position, 1, true});
  }
  ```

- **Kolizja z twardą cegłą**:

  ```cpp
  if (!brick.indestructible) {
      brick.health--;
      if (brick.health == 0) {
          bricks.erase(it);
      }
  }
  ```
  