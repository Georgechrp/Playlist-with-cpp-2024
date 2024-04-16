#include <iostream>
#include <string>
//Για την τυχαία αναπαραγωγή
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>


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

    // Εκτύπωση της λίστας αναπαραγωγής
    void printSongs() const {
        std::cout << name << ": " << std::endl;
        ChainNode<Song>* current = songs.getHead();
        while (current != nullptr) {
            std::cout << "Title: " << current->data.getTitle() << ", Artist: " << current->data.getArtistName() << " " << current->data.getArtistSurname() << ", Album: " << current->data.getAlbumTitle() << ", Likes: " << current->data.getLikes() << std::endl;
            current = current->next;
        }
    }
    // Αναπαραγωγη επόμενου τραγουδιού
    void playNextSong(ChainNode<Song>** current) const {
        if (*current != nullptr && (*current)->next != nullptr) {
            *current = (*current)->next;
            std::cout << "Next song: " << (*current)->data.getTitle() << std::endl;
        }
        else {
            std::cout << "No next song in the playlist." << std::endl;
        }
    }
    void playPrevSong(ChainNode<Song>** current) const {
        if (*current != nullptr && (*current)->prev != nullptr) {
            *current = (*current)->prev;
            std::cout << "Previous song: " << (*current)->data.getTitle() << std::endl;
        }
        else {
            std::cout << "No previous song in the playlist." << std::endl;
        }
    }


    void playShuffled() const {
        // Δημιουργούμε έναν πίνακα που θα περιέχει τους δείκτες σε κάθε τραγούδι της λίστας
        std::vector<const ChainNode<Song>*> songPointers;
        ChainNode<Song>* current = songs.getHead();
        while (current != nullptr) {
            songPointers.push_back(current);
            current = current->next;
        }

        // Ανακατεύουμε τους δείκτες στον πίνακα
        std::srand(std::time(0));
        std::random_shuffle(songPointers.begin(), songPointers.end());

        // Αναπαράγουμε τα τραγούδια σύμφωνα με τη σειρά τους στον ανακατεμένο πίνακα
        for (const auto& songPtr : songPointers) {
            std::cout << "Playing song \"" << songPtr->data.getTitle() << "\" from the album \"" << songPtr->data.getAlbumTitle() << "\" with singer \"" << songPtr->data.getArtistName() << " " << songPtr->data.getArtistSurname() << "\" (" << songPtr->data.getLikes() << " users like this song)" << std::endl;
        }
    }

};

//Ορισμός της κλάσης insertSong
void insertSong(Playlist& myPlaylist) {
    // Δημιουργία μιας λίστας αναπαραγωγής με τραγούδια
    std::string title;
    std::string artistName;
    std::string artistSurname;
    std::string albumTitle;
    int likes;
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
    Song song1(title, artistName, artistSurname, albumTitle, likes);
    myPlaylist.addSong(song1);
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


    myPlaylist.printSongs();
    ChainNode<Song>* current = myPlaylist.findHead();

    int choice, choiceForSort;
    do {
        std::cout << "\nPlaying song \"" << current->data.getTitle() << "\" from the album \"" << current->data.getAlbumTitle() << "\" with the singer \"" << current->data.getArtistName() + " " + current->data.getArtistSurname() << "\" (" << current->data.getLikes() << "users like this song)";
        std::cout << "\n\nMenu:" << std::endl;
        std::cout << "1. Insert new song into playlist" << std::endl;
        std::cout << "2. Play next song in playlist" << std::endl;
        std::cout << "3. Play previous song in playlist" << std::endl;
        std::cout << "4. Play all songs in playlist in random order" << std::endl;
        std::cout << "5. Move song to another position in playlist" << std::endl;
        std::cout << "6. Sort playlist" << std::endl;
        std::cout << "7. Print playlist to screen" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Enter your choice: \n";
        std::cin >> choice;


        switch (choice) {
        case 1:
            insertSong(myPlaylist);
            break;
        case 2:
        { //ChainNode<Song>* current = nullptr;
            myPlaylist.playNextSong(&current);
            std::cout << " " << std::endl;
            break;
        }
        case 3:
            myPlaylist.playPrevSong(&current);
            std::cout << " " << std::endl;
            break;
        case 4:
            //myPlaylist.playShuffled();
            std::cout << " " << std::endl;
            break;
        case 5:
            //moveSong(playlist);
            std::cout << " " << std::endl;
            break;
        case 6:
            std::cout << "\nMenu for Sorting:" << std::endl;
            std::cout << "1. Sort playlist by song title" << std::endl;
            std::cout << "2. Sort playlist by singer’s first name" << std::endl;
            std::cout << "3. Sort playlist by singer’s last name" << std::endl;
            std::cout << "4. Sort playlist by number of likes (decreasing)" << std::endl;
            std::cout << "5. Cancel sorting" << std::endl;
            std::cin >> choiceForSort;
            switch (choice) {
            case 1:
                std::cout << "Sort playlist by song title" << std::endl;
                break;
            case 2:
                std::cout << "2. Sort playlist by singer’s first name" << std::endl;
                break;
            case 3:
                std::cout << "3. Sort playlist by singer’s last name" << std::endl;
                break;
            case 4:
                std::cout << "4. Sort playlist by number of likes (decreasing)" << std::endl;
                break;
            case 5:
                break;
            }
            //sortPlaylist(playlist);
            std::cout << " " << std::endl;
            break;
        case 7:
            myPlaylist.printSongs();
            break;
        case 8:
            //cout << "Exiting..." << endl;
            std::cout << " " << std::endl;
            break;
            //default:
            //    // cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
        }
    } while (choice != 8);

    return 0;

}