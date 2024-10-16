﻿#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>

// Ορισμός του κόμβου αλυσίδας
template <typename T>
class ChainNode {
public:
    T data;
    ChainNode<T>* next;
    ChainNode<T>* prev;

    ChainNode(const T& data) : data(data), next(nullptr), prev(nullptr) {}
};

// Ορισμός της αλυσίδας
template <typename T>
class Chain {
private:
    ChainNode<T>* head;
    ChainNode<T>* tmp;

public:
    Chain() : head(nullptr) {}

    void addNode(const T& data) {
        ChainNode<T>* newNode = new ChainNode<T>(data);
        if (head == nullptr) {
            head = newNode;
            tmp = head;
        }
        else {
            tmp->next = newNode;
            tmp->next->prev = tmp;
            tmp = tmp->next;
        }
    }

    void addNode(const T& data, int position) {
        ChainNode<T>* newNode = new ChainNode<T>(data);
        if (head == nullptr) {
            head = newNode;
            tmp = head;
        }
        else {
            // Ειδική περίπτωση για την πρώτη θέση
            if (position == 0) {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            else {
                ChainNode<T>* current = head;
                int currentPosition = 0;
                while (current != nullptr && currentPosition < position - 1) {
                    current = current->next;
                    currentPosition++;
                }
                if (current == nullptr) {
                    std::cerr << "Invalid position. Node was not added." << std::endl;
                    delete newNode;
                    return;
                }
                newNode->next = current->next;
                if (current->next != nullptr) {
                    current->next->prev = newNode;
                }
                current->next = newNode;
                newNode->prev = current;
            }
        }
    }

    // Εκτύπωση της αλυσίδας
    void print() const {
        ChainNode<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Επιστρέφει τον δείκτη στην κορυφαία δεσμίδα της αλυσίδας
    ChainNode<T>* getHead() const {
        return head;
    }


};

// Ορισμός της κλάσης Song
class Song {
private:
    std::string title;
    std::string artistName;
    std::string artistSurname;
    std::string albumTitle;
    int likes;

public:
    // Constructor
    Song(const std::string& title, const std::string& artistName, const std::string& artistSurname, const std::string& albumTitle, int likes)
        : title(title), artistName(artistName), artistSurname(artistSurname), albumTitle(albumTitle), likes(likes) {}

    // Getters
    std::string getTitle() const { return title; }
    std::string getArtistName() const { return artistName; }
    std::string getArtistSurname() const { return artistSurname; }
    std::string getAlbumTitle() const { return albumTitle; }
    int getLikes() const { return likes; }

};

// Ορισμός της κλάσης Playlist
class Playlist {
private:
    std::string name;
    Chain<Song> songs; // Η διπλά συνδεδεμένη λίστα τραγουδιών
public:
    Playlist(const std::string& name) : name(name) {}
    ChainNode<Song>* findHead() const {
        return songs.getHead();
    }

    // Προσθήκη τραγουδιού στη λίστα αναπαραγωγής
    void addSong(const Song& song) {
        songs.addNode(song);
    }

    // Προσθήκη τραγουδιού στη λίστα αναπαραγωγής
    void addSong(const Song& song, int pos) {
        songs.addNode(song, pos);
    }

    // Εκτύπωση της λίστας αναπαραγωγής
    void printSongs() const {
        int songCount = 1;
        std::cout << name << ": " << std::endl;
        ChainNode<Song>* current = songs.getHead();
        while (current != nullptr) {
            std::cout << songCount++;
            std::cout << ".Title: " << current->data.getTitle() << ", Artist: " << current->data.getArtistName() << " " << current->data.getArtistSurname() << ", Album: " << current->data.getAlbumTitle() << ", Likes: " << current->data.getLikes() << std::endl;
            current = current->next;
        }
    }

    // Αναπαραγωγη επόμενου τραγουδιού
    void playNextSong(ChainNode<Song>** current) const {
        if (*current != nullptr && (*current)->next != nullptr) {
            *current = (*current)->next;
            std::cout << "\nThe Next song: " << (*current)->data.getTitle() << std::endl;
        }
        else {
            std::cout << "\nNo next song in the playlist." << std::endl;
        }
    }
    void playPrevSong(ChainNode<Song>** current) const {
        if (*current != nullptr && (*current)->prev != nullptr) {
            *current = (*current)->prev;
            std::cout << "\nThe Previous song: " << (*current)->data.getTitle() << std::endl;
        }
        else {
            std::cout << "\nNo previous song in the playlist." << std::endl;
        }
    }

    // Μέθοδος για τον υπολογισμό του μήκους της λίστας
    int getLength() const {
        int length = 0;
        ChainNode<Song>* current = findHead();
        while (current != nullptr) {
            ++length;
            current = current->next;
        }
        return length;
    }

    // Μέθοδος για ταξινόμηση των τραγουδιών κατά τίτλο
    void sortSongsByTitle(Playlist myplaylist) {
        
        if (myplaylist.findHead() == nullptr || myplaylist.findHead()->next == nullptr) {
            // Η λίστα είναι ήδη ταξινομημένη ή περιέχει μόνο ένα στοιχείο
            return;
        }

        bool swapped;
        ChainNode<Song>* ptr1;
        ChainNode<Song>* lptr = nullptr;
        do {
            swapped = false;
            ptr1 = myplaylist.findHead();

            while (ptr1->next != lptr) {
                if (ptr1->data.getTitle() > ptr1->next->data.getTitle()) {
                    swap(ptr1, ptr1->next);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }

    // Μέθοδος για ταξινόμηση των τραγουδιών κατά όνομα 
    void sortSongsByFirstName(Playlist myplaylist) {

        if (myplaylist.findHead() == nullptr || myplaylist.findHead()->next == nullptr) {
            // Η λίστα είναι ήδη ταξινομημένη ή περιέχει μόνο ένα στοιχείο
            return;
        }

        bool swapped;
        ChainNode<Song>* ptr1;
        ChainNode<Song>* lptr = nullptr;
        do {
            swapped = false;
            ptr1 = myplaylist.findHead();

            while (ptr1->next != lptr) {
                if (ptr1->data.getArtistName() > ptr1->next->data.getArtistName()) {
                    swap(ptr1, ptr1->next);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }

    // Μέθοδος για ταξινόμηση των τραγουδιών με επίθετο 
    void sortSongsByLastName(Playlist myplaylist) {

        if (myplaylist.findHead() == nullptr || myplaylist.findHead()->next == nullptr) {
            // Η λίστα είναι ήδη ταξινομημένη ή περιέχει μόνο ένα στοιχείο
            return;
        }

        bool swapped;
        ChainNode<Song>* ptr1;
        ChainNode<Song>* lptr = nullptr;
        do {
            swapped = false;
            ptr1 = myplaylist.findHead();

            while (ptr1->next != lptr) {
                if (ptr1->data.getArtistSurname() > ptr1->next->data.getArtistSurname()) {
                    swap(ptr1, ptr1->next);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }

    // Μέθοδος για ταξινόμηση των τραγουδιών με likes 
    void sortSongsByLikes(Playlist myplaylist) {

        if (myplaylist.findHead() == nullptr || myplaylist.findHead()->next == nullptr) {
            // Η λίστα είναι ήδη ταξινομημένη ή περιέχει μόνο ένα στοιχείο
            return;
        }

        bool swapped;
        ChainNode<Song>* ptr1;
        ChainNode<Song>* lptr = nullptr;
        do {
            swapped = false;
            ptr1 = myplaylist.findHead();

            while (ptr1->next != lptr) {
                if (ptr1->data.getLikes() < ptr1->next->data.getLikes()) {
                    swap(ptr1, ptr1->next);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }


    // Βοηθητική μέθοδος για ανταλλαγή δεικτών
    void swap(ChainNode<Song>* a, ChainNode<Song>* b) {
        Song temp = a->data;
        a->data = b->data;
        b->data = temp;
    }

    //Επιστρέφει το τραγούδι που βρίσκεται στην θέση pos
    ChainNode<Song>* findSongWithPosition(int pos) {
        int songCount = 1;
        ChainNode<Song>* current = songs.getHead();
        while (current != nullptr && songCount != pos) {
            songCount++;
            current = current->next;
        } 
        
        return current;
    }

    void moveSongs(int pos1, int pos2) {
        ChainNode<Song>* node1 = findSongWithPosition(pos1);
        ChainNode<Song>* node2 = findSongWithPosition(pos2);
        swap(node1, node2);
        //swap(findSongWithPosition(pos1), findSongWithPosition(pos2));
    }
  
    int giveRandomNumber() {
        int lowerBound = 1; // Κάτω όριο
        int upperBound = getLength(); // Άνω όριο

        // Δημιουργία ενός γεννήτριας τυχαίων αριθμών
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(lowerBound, upperBound);

        // Δημιουργία τυχαίου αριθμού μεταξύ lowerBound και upperBound
        int randomNumber = dist(gen);

        return randomNumber;
    }
    //Ανακατευουμε
    void Suffle() {
        for (int i = 0; i < getLength() + 10; i++) {
            swap(findSongWithPosition(giveRandomNumber()), findSongWithPosition(giveRandomNumber()));
        }
        std::cout << "random order successful! Press '7' to see the order\n";
    }
};

//Ορισμός της κλάσης insertSong
void insertSong(Playlist& myPlaylist) {
    // Δημιουργία μιας λίστας αναπαραγωγής με τραγούδια
    std::string title;
    std::string artistName;
    std::string artistSurname;
    std::string albumTitle;
    int likes, pos;
    std::cout << "\nEnter title of song: ";
    std::cin >> title;
    std::cout << "\nEnter name of singer: ";
    std::cin >> artistName;
    std::cout << "\nEnter surname of singer: ";
    std::cin >> artistSurname;
    std::cout << "\nEnter title of album: ";
    std::cin >> albumTitle;
    std::cout << "\nEnter number of likes: ";
    std::cin >> likes;
    std::cout << "\nEnter position in playlist: ";
    std::cin >> pos;
    Song song1(title, artistName, artistSurname, albumTitle, likes);
    myPlaylist.addSong(song1, pos - 1);
    std::cout << "Song added successfully" << std::endl;
}


void initializeThePlaylist(Playlist& myPlaylist) {
    Song song1("Balada", "Foivos", "Delivorias", "ANIME", 1946);
    Song song2("Ligo akoma", "Novel", "729", "Vioma", 12347);
    Song song3("Kathe Mera", "Bloody", "Hawk", "The Deal", 2837);
    Song song4("Bietnam ye ye", "Dionysis", "Sabbopoulos", "Fortigo", 3200);
    Song song5("Atairiasto", "Foivos", "Delivorias", "ANIME", 2946);
    Song song6("Mono Psemata", "Foivos", "Delivorias", "ANIME", 2946);
    Song song7("Oi palioi mas filoi", "Dionysis", "Sabbopoulos", "Fortigo", 3200);
    myPlaylist.addSong(song1);
    myPlaylist.addSong(song2);
    myPlaylist.addSong(song3);
    myPlaylist.addSong(song4);
    myPlaylist.addSong(song5);
    myPlaylist.addSong(song6);
    myPlaylist.addSong(song7);
}

int main() {
    Playlist myPlaylist("The Best Playlist ever");
    initializeThePlaylist(myPlaylist);
    ChainNode<Song>* current = myPlaylist.findHead();

    bool flag;
    int choice, choiceForSort, pos1, pos2;
    do {
        std::cout << "_______________________________________________________________________________________________________________\n";
        std::cout << "\n  Playing song \"" << current->data.getTitle() << "\" from the album \"" << current->data.getAlbumTitle() << "\" with the singer \"" << current->data.getArtistName() + " " + current->data.getArtistSurname() << "\" (" << current->data.getLikes() << " users like this song)";
        std::cout << "\n_______________________________________________________________________________________________________________\n";
        std::cout << "\n - - - - - - - - - - Menu - - - - - - - - - - - -" << std::endl;
        std::cout << " | 1. Insert new song into playlist             |" << std::endl;
        std::cout << " | 2. Play next song in playlist                |" << std::endl;
        std::cout << " | 3. Play previous song in playlist            |" << std::endl;
        std::cout << " | 4. Play all songs in playlist in random order|" << std::endl;
        std::cout << " | 5. Move song to another position in playlist |" << std::endl;
        std::cout << " | 6. Sort playlist                             |" << std::endl;
        std::cout << " | 7. Print playlist to screen                  |" << std::endl;
        std::cout << " | 8. Exit                                      |" << std::endl;
        std::cout << " - - - - - - - - - - - - - - - - - - - - - - - -\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            insertSong(myPlaylist);
            break;
        case 2:
            myPlaylist.playNextSong(&current);//ChainNode<Song>* current = nullptr;
            break;
        case 3:
            myPlaylist.playPrevSong(&current);
            break;
        case 4:
            myPlaylist.Suffle();
            break;
        case 5:
            do {
                flag = true;
                std::cout << "Enter position of song in playlist to move: ";
                std::cin >> pos1;
                std::cout << "\nEnter new position of song in playlist : ";
                std::cin >> pos2;
                if (pos1<1 || pos1>myPlaylist.getLength()) {
                    std::cout << "\nPlease enter a number bewteen 1 and " << myPlaylist.getLength();
                    flag = false;
                }
                if (pos2<1 || pos2>myPlaylist.getLength()) {
                    std::cout << "\nPlease enter a number bewteen 1 and " << myPlaylist.getLength() << "\n";
                    flag = false;
                }
                
            } while (!flag);
            myPlaylist.moveSongs(pos1, pos2);
            std::cout << "\n - - The songs in order " << pos1 << " and " << pos2 << " reversed  - - \n";
            break;
        case 6:
            std::cout << "\nMenu for Sorting:" << std::endl;
            std::cout << "1. Sort playlist by song title" << std::endl;
            std::cout << "2. Sort playlist by singer’s first name" << std::endl;
            std::cout << "3. Sort playlist by singer’s last name" << std::endl;
            std::cout << "4. Sort playlist by number of likes (decreasing)" << std::endl;
            std::cout << "5. Cancel sorting" << std::endl;
            std::cin >> choiceForSort;
            switch (choiceForSort) {
            case 1:
                myPlaylist.sortSongsByTitle(myPlaylist);
                std::cout << "[Playlist sorted by song title]" << std::endl;
                break;
            case 2:
                myPlaylist.sortSongsByFirstName(myPlaylist);
                std::cout << "[Playlist sorted by First Name]" << std::endl;
                break;
            case 3:
                myPlaylist.sortSongsByLastName(myPlaylist);
                std::cout << "[Playlist sorted by Last Name]" << std::endl;
                break;
            case 4:
                myPlaylist.sortSongsByLikes(myPlaylist);
                std::cout << "[Playlist sorted by Likes(decreasing)]" << std::endl;
                break;
            case 5:
                break;
            }
            std::cout << "[Press '7' to see the sorted playlist]" << std::endl;
            break;
        case 7:
            myPlaylist.printSongs();
            break;
        case 8:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 8." << std::endl;
        }
    } while (choice != 8);

    return 0;

}