#include <iostream>
using namespace std;

class Playlist {       
private:
    string playlistName;  
};

class Song {
private:
    string title;
    string singerName;
    string singerSurname;
    string titleAlbum;
    int likes;

};


void insertSong() {
    // Ζήτηση πληροφοριών από τον χρήστη για το τραγούδι
    string title, singerName, singerSurname, albumTitle;
    int likes, position;
    cout << "Enter title of song: ";
    cin >> title ;
    cout << "Enter name of singer: ";
    cin >> singerName;
    cout << "Enter surname of singer: ";
    cin >> singerSurname;
    cout << "Enter title of album: ";
    cin >> albumTitle;
    cout << "Enter number of likes: ";
    cin >> likes;
    cout << "Enter position in playlist: ";
    cin >> position;
}

int main()
{
    Playlist playlist1;

    cout << "     MENU      /n";
    cout << "1.Insert new song into playlist" << endl;
    cout << "2.Play next song in playlist" << endl;
    cout << "3.Play previous song in playlist" << endl;
    cout << "4.Play all songs in playlist in random order" << endl;
    cout << "5.Move song to another position in playlist" << endl;
    cout << "6.Sort playlist" << endl;
    cout << "7.Print playlist to screen" << endl;
    cout << "8.EXIT" << endl;

    int ch;
    if (ch == 1) {
        insertSong();
    }

    
}
