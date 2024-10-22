#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <thread>
#include <limits>
#include <conio.h>

using namespace std;

// Global variable untuk bahasa
string language;

// Fungsi untuk menampilkan pesan loading
void loading() {
    cout << "Loading ";
    for (int i = 0; i <= 100; i += 10) {
        cout << ".";
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << endl;
}

// Fungsi untuk memilih bahasa
void selectLanguage() {
    int choice;
    cout << "Select Language:\n1. Indonesian\n2. English\n";
    cin >> choice;

    if (choice == 1) {
        language = "Indonesian";
    } else {
        language = "English";
    }
}

// Fungsi untuk mendapatkan pilihan yang valid
int getValidChoice(int min, int max) {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail() || choice < min || choice > max) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << (language == "Indonesian" ? "Pilihan tidak valid. Silakan coba lagi: " : "Invalid choice. Please try again: ");
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
            return choice;
        }
    }
}

// Game 1: Tebak Angka
void playGuessNumber() {
    loading();
    cout << (language == "Indonesian" ? "Permainan Tebak Angka" : "Guess the Number Game") << endl;
    int number = rand() % 100 + 1;
    int guess;

    while (true) {
        cout << (language == "Indonesian" ? "Tebak angka (1-100): " : "Guess a number (1-100): ");
        guess = getValidChoice(1, 100);

        if (guess == number) {
            cout << (language == "Indonesian" ? "Selamat! Anda menebak angka!" : "Congratulations! You guessed the number!") << endl;
            break;
        } else if (guess > number) {
            cout << (language == "Indonesian" ? "Terlalu tinggi!" : "Too high!") << endl;
        } else {
            cout << (language == "Indonesian" ? "Terlalu rendah!" : "Too low!") << endl;
        }
    }
}

// Game 2: Batu, Kertas, Gunting
void playRockPaperScissors() {
    loading();
    cout << (language == "Indonesian" ? "Permainan Batu, Kertas, Gunting" : "Rock, Paper, Scissors Game") << endl;

    int playerChoice;
    cout << (language == "Indonesian" ? "Pilih: 1. Batu 2. Kertas 3. Gunting: " : "Choose: 1. Rock 2. Paper 3. Scissors: ");
    playerChoice = getValidChoice(1, 3);

    int computerChoice = rand() % 3 + 1;

    if (playerChoice == computerChoice) {
        cout << (language == "Indonesian" ? "Seri!" : "Draw!") << endl;
    } else if ((playerChoice == 1 && computerChoice == 3) ||
               (playerChoice == 2 && computerChoice == 1) ||
               (playerChoice ==  3 && computerChoice == 2)) {
        cout << (language == "Indonesian" ? "Anda menang!" : "You win!") << endl;
    } else {
        cout << (language == "Indonesian" ? "Anda kalah!" : "You lose!") << endl;
    }
}

// Game 3: Tic Tac Toe
void playTicTacToe() {
    loading();
    cout << (language == "Indonesian" ? "Permainan Tic Tac Toe" : "Tic Tac Toe Game") << endl;

    char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    char player = 'X';
    int choice;

    for (int i = 0; i < 9; i++) {
        cout << "Papan:\n";
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                cout << board[row][col] << " ";
            }
            cout << endl;
        }

        cout << (language == "Indonesian" ? "Giliran " : "Turn ") << player << ", pilih posisi: ";
        choice = getValidChoice(1, 9) - 1; // Sesuaikan dengan index array
        int row = choice / 3;
        int col = choice % 3;

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            cout << (language == "Indonesian" ? "Pilihan tidak valid." : "Invalid choice.") << endl;
            i--; // Mengurangi giliran karena pilihan tidak valid
            continue;
        }

        board[row][col] = player;

        // Cek kemenangan
        for (int j = 0; j < 3; j++) {
            if ((board[j][0] == player && board[j][1] == player && board[j][2] == player) || // Baris
                (board[0][j] == player && board[1][j] == player && board[2][j] == player)) { // Kolom
                cout << (language == "Indonesian" ? "Pemain " : "Player ") << player << " menang!" << endl;
                return;
            }
        }
        if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || // Diagonal
            (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
            cout << (language == "Indonesian" ? "Pemain " : "Player ") << player << " menang!" << endl;
            return;
        }

        // Ganti giliran
        player = (player == 'X') ? 'O' : 'X';
    }

    cout << (language == "Indonesian" ? "Permainan seri!" : "Game is a draw!") << endl;
}

// Game 4: Snake
void playSnake() {
    loading();
    cout << (language == "Indonesian" ? "Permainan Snake" : "Snake Game") << endl;

    int snakeLength = 3, snakeX = 5, snakeY = 5, foodX = rand() % 10, foodY = rand() % 10;
    char direction = 'R'; // R = Right, L = Left, U = Up, D = Down

    while (true) {
        system("CLS");
        cout << "Panjang ular: " << snakeLength << endl;
        cout << "Ular berada di: (" << snakeX << ", " << snakeY << ")" << endl;
        cout << "Makanan berada di: (" << foodX << ", " << foodY << ")" << endl;

        char input = _getch();
        if (input == 'w') direction = 'U'; // Up
        else if (input == 's') direction = 'D'; // Down
        else if (input == 'a') direction = 'L'; // Left
        else if (input == 'd') direction = 'R'; // Right
        else if (input == 'q') break; // Keluar

        // Update posisi ular
        if (direction == 'U') snakeY--;
        else if (direction == 'D') snakeY++;
        else if (direction == 'L') snakeX--;
        else if (direction == 'R') snakeX++;

        // Cek makanan
        if (snakeX == foodX && snakeY == foodY) {
            snakeLength++;
            foodX = rand() % 10;
            foodY = rand() % 10;
        }

        if (snakeX < 0 || snakeX >= 10 || snakeY < 0 || snakeY >= 10) {
            cout << (language == "Indonesian" ? "Ular keluar dari layar!" : "Snake exited the screen!") << endl;
            break;
        }
    }
}

// Game 5: Balap Mobil
void playCarRacing() {
    loading();
    cout << (language == "Indonesian" ? "Permainan Balap Mobil" : "Car Racing Game") << endl;

    int playerPosition = 0, finishLine = 100;
    cout << (language == "Indonesian" ? "Tekan 'f' untuk mempercepat, 'q' untuk keluar ." : "Press 'f' to accelerate, 'q' to quit.") << endl;

    while (true) {
        char input = _getch();
        if (input == 'f') {
            playerPosition += 10;
            cout << "Anda sekarang di posisi: " << playerPosition << endl;
        } else if (input == 'q') {
            break;
        }

        if (playerPosition >= finishLine) {
            cout << (language == "Indonesian" ? "Anda menang!" : "You win!") << endl;
            break;
        }
    }
}

// Game 6: Tebak Kata
void playGuessWord() {
    loading();
    cout << (language == "Indonesian" ? "Permainan Tebak Kata" : "Guess the Word Game") << endl;

    string words[] = {"apel", "jeruk", "pisang", "mangga"};
    string word = words[rand() % 4];
    string guessed(word.size(), '_');
    char letter;

    while (guessed != word) {
        cout << "Tebak kata: " << guessed << endl;
        cout << "Tebak huruf: ";
        cin >> letter;

        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == letter) {
                guessed[i] = letter;
            }
        }
    }

    cout << (language == "Indonesian" ? "Selamat! Anda menebak kata!" : "Congratulations! You guessed the word!") << endl;
}

// Game 7: Mencocokkan Warna
void playColorMatching() {
    loading();
    cout << (language == "Indonesian" ? "Permainan Mencocokkan Warna" : "Color Matching Game") << endl;

    vector<string> colors = {"merah", "biru", "hijau", "kuning"};
    string colorToMatch = colors[rand() % colors.size()];

    cout << (language == "Indonesian" ? "Cocokkan warna: " : "Match the color: ") << colorToMatch << endl;

    string guess;
    cin >> guess;

    if (guess == colorToMatch) {
        cout << (language == "Indonesian" ? "Anda menang!" : "You win!") << endl;
    } else {
        cout << (language == "Indonesian" ? "Anda kalah!" : "You lose!") << endl;
    }
}

// Game 8: Bingo
void playBingo() {
    loading();
    cout << (language == "Indonesian" ? "Permainan Bingo" : "Bingo Game") << endl;

    vector<int> numbers(25);
    for (int i = 0; i < 25; ++i) {
        numbers[i] = i + 1;
    }
    random_shuffle(numbers.begin(), numbers.end());

    cout << "Pilih nomor antara 1-25: ";
    int choice = getValidChoice(1, 25);

    if (numbers[choice - 1] == choice) {
        cout << (language == "Indonesian" ? "Anda menang!" : "You win!") << endl;
    } else {
        cout << (language == "Indonesian" ? "Anda kalah!" : "You lose!") << endl;
    }
}

// Game 9: Memori
void playMemory() {
    loading();
    cout << (language == "Indonesian" ? "Permainan Memori" : "Memory Game") << endl;

    vector<int> cards = {1, 2, 1, 2, 3, 4, 3, 4}; // Contoh sederhana
    random_shuffle(cards.begin(), cards.end());

    vector<bool> revealed(cards.size(), false);
    int firstGuess = -1, secondGuess = -1;

    for (int i = 0; i < 2; ++i) {
        cout << "Tebak pasangan kartu (1-4): " << endl;
        int guess = getValidChoice(1, 4);
        guess--; // Menyesuaikan index

        cout << "Anda memilih kartu: " << guess + 1 << endl;

        // Logika pencocokan pasangan
        if (cards[guess] == firstGuess) {
            cout << "Kartu yang dipilih: " << cards[guess] << endl;
            revealed[guess] = true;
            if (i == 1) {
                cout << (language == "Indonesian" ? "Anda menang!" : "You win!") << endl;
                return;
            }
        } else {
            if (i == 0) {
                firstGuess = cards[guess];
            } else {
                secondGuess = cards[guess];
            }
        }
    }

    cout << (language == "Indonesian" ? "Anda kalah!" : "You lose!") << endl;
}

// Game 10: Ular Tangga
void playSnakesAndLadders() {
    loading();
    cout << (language == "Indonesian" ? "Permainan Ular Tangga" : "Snakes and Ladders Game") << endl;

    int position = 0;

    while (position < 100) {
        cout << "Tekan 'd' untuk melempar dadu: ";
        char input = _getch();
        if (input == 'd') {
            int roll = rand() % 6 + 1;
            position += roll;
            if (position > 100) position = 100; // Tidak lebih dari 100
            cout << "Anda mendapatkan " << roll << ", posisi Anda sekarang: " << position << endl;

            // Cek apakah ada ular atau tangga
            if (position == 10) {
                cout << (language == "Indonesian" ? "Anda mendapatkan ular! Posisi Anda sekarang: 5" : "You got a snake! Your position is now: 5") << endl;
                position = 5;
            } else if (position == 20) {
                cout << (language == "Indonesian" ? "Anda mendapatkan tangga! Posisi Anda sekarang: 30" : "You got a ladder! Your position is now: 30") << endl;
                position = 30;
            }

            if (position == 100) {
                cout << (language == "Indonesian" ? "Selamat! Anda menang!" : "Congratulations! You win!") << endl;
                break;
            }
        }
    }
}

// Menu Utama
void mainMenu() {
    while (true) {
        cout << (language == "Indonesian" ? "Pilih permainan:\n1. Tebak Angka\n2. Batu, Kertas, Gunting\n3. Tic Tac Toe\n4. Snake\n5. Balap Mobil\n6. Tebak Kata\n7. Mencocokkan Warna\n8. Bingo\n9. Memori\n10. Ular Tangga\n11. Keluar\n" :
            "Select a game:\n1. Guess the Number\n2. Rock, Paper, Scissors\n3. Tic Tac Toe\n4. Snake\n5. Car Racing\n6. Guess the Word\n7. Color Matching\n8. Bingo\n9. Memory\n10. Snakes and Ladders\n11. Exit\n");
        
        int choice = getValidChoice(1, 11);
        
        switch (choice) {
            case 1: playGuessNumber(); break;
            case 2: playRockPaperScissors(); break;
            case 3: playTicTacToe(); break;
            case 4: playSnake(); break;
            case 5: playCarRacing(); break;
            case 6: playGuessWord(); break;
            case 7: playColorMatching(); break;
            case 8: playBingo(); break;
            case 9: playMemory(); break;
            case 10: playSnakesAndLadders(); break;
            case 11: return;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    selectLanguage();
    mainMenu();
    return 0;
}
