#include <vector>
#include <string>
#include <queue>
#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "TVseries.hpp"
#include <iostream>

using namespace std;


// implementation of class TVSeries

TVSeries::TVSeries(string seriesTitle, int seasons, vector<int> episodesPerSeason, string seriesGenre, float seriesRating, bool isFinished) :
    title(seriesTitle), numberOfSeasons(seasons), episodesPerSeason(episodesPerSeason), genre(seriesGenre), rating(seriesRating), finished(isFinished) {};

string TVSeries::getTitle() const { return title; }

int TVSeries::getNumberOfSeasons() const { return numberOfSeasons; }

vector<int> TVSeries::getEpisodesPerSeason() const { return episodesPerSeason; }

string TVSeries::getGenre() const { return genre; }

float TVSeries::getRating() const { return rating; }

bool TVSeries::isFinished() const { return finished; }

void TVSeries::displaySeriesInfo() const
{
    cout << "Displaying TV series info:" << endl;
    cout << "-----Title: " << title << endl;
    cout << "-----Number of Seasons: " << numberOfSeasons << endl;
    cout << "-----Episodes per Season:" << endl;
    for (size_t i = 0; i < episodesPerSeason.size(); ++i) {
        cout << "-----Season " << (i + 1) << ": " << episodesPerSeason[i] << " episodes" << endl;
    }
    cout << "-----Genre: " << genre << endl;
    cout << "-----Rating: " << rating << endl;
    cout << "-----Finished: " << (finished ? "Yes" : "No") << endl;
}


float TVSeries::updateRating(const vector<User*>& vectorUser)
{
    if (vectorUser.empty()) {
        cout << "Error: No users provided." << endl;
        return -1; // Return -1 in case of error
    }

    float totalRating = 0;
    int numRatings = 0;

    // Iterate through each user
    for ( User* user : vectorUser) {
        // Check if the user watched this series
        vector<TVSeries*> &watchedSeries = user->getWatchedSeries();
        auto it = find(watchedSeries.begin(), watchedSeries.end(), this);
        if (it != watchedSeries.end()) {
            // User watched this series, get the rating
            int index = distance(watchedSeries.begin(), it);
            totalRating += user->getRatings()[index];
            numRatings++;
        }
    }

    // Calculate the average rating
    if (numRatings > 0) {
        rating = totalRating / numRatings;
        return rating;
    } else {
        cout << "Error: No users have rated this series." << endl;
        return 0; // Return 0 
    }
}
bool TVSeries::operator <(const TVSeries& tv) const
    {
        // this will return true when second TVSeries
        // has greater rating. Suppose we have tv1.rating=5
        // and tv2.rating=5.5 then the object which
        // have max rating will be at the top(or
        // max priority)
         return this->rating < tv.rating;
    }
// implementation of class User

User::User(string uname, string completeName, string userCountry, vector<string> genres) :
    username(uname), name(completeName), country(userCountry), favoriteGenres(genres) {};

string User::getUsername() const { return username; }

string User::getName() const { return name; }

vector<string> User::getFavoriteGenres() const { return favoriteGenres; }

vector<TVSeries*>& User::getWatchedSeries() { return watchedSeries; }

vector<int>& User::getRatings()  { return ratings; }

vector<int>& User::getEpisodesWatched()  { return episodesWatched; }

queue<TVSeries*>& User::getWishSeries()   { return wishSeries; }

int User::addFavoriteGenre(int genreIdx)
{
    // Check if the index of the genre exists in 'vGenres'
    if (!(genreIdx >= 0 && genreIdx < N_GENRES)) return -1;

    // Check if the genre already exists in the vector
    if (find(favoriteGenres.begin(), favoriteGenres.end(), vGenres[genreIdx]) == favoriteGenres.end()) {
        // Genre doesn't exist, so add it to the vector
        favoriteGenres.push_back(vGenres[genreIdx]);
    }

    // Genre already exists, do nothing
    cout << "Genre already exists in favorite genres." << endl;
    return 1;
}

int User::addWatchedSeries(TVSeries* series)
{
    // Check if the series pointer is valid
    if (series == nullptr) {
        cout << "Error: Invalid series pointer." << endl;
        return -1; // Return -1 to indicate an error
    }

    // Check if the series is already in watchedSeries
    auto it = find(watchedSeries.begin(), watchedSeries.end(), series);
    if (it != watchedSeries.end()) {
   //     cout << "Series is already in watched series." << endl;
        return 1; // Series already exists, no need to insert
    }

    // Series is not in watchedSeries, so insert it
    watchedSeries.push_back(series);
    episodesWatched.push_back(0); // Initialize episodesWatched for the new series
    ratings.push_back(0);
  //  cout << "New watched series inserted." << endl;
    return 0; // Successfully inserted
}
int User::addWishSeries(TVSeries* series)
{
    // Check if the series pointer is valid
    if (series == nullptr) {
        cout << "Error: Invalid series pointer." << endl;
        return -1; // Return -1 to indicate an error
    }

    // Check if the series is already in watchedSeries
    queue<TVSeries*> aux;
    bool teste=false;
    while(!wishSeries.empty())
    {
        if (wishSeries.front()==series)
        {
            teste=true;
        }
        aux.push(wishSeries.front());
        wishSeries.pop();
    }
    while(!aux.empty())
    {
        wishSeries.push(aux.front());
        aux.pop();
    }
    if (teste) return -1;
    // Series is not in wishSeries, so insert it
    wishSeries.push(series);
 
   // cout << "New wish series inserted." << endl;
    return 0; // Successfully inserted
}

int User::addEpisodesWatched(TVSeries* series, int n)
{
    // Check if the series pointer is valid
    if (series == nullptr) {
        cout << "Error: Invalid series pointer." << endl;
        return -1; // Exit the function if the series pointer is invalid
    }

    // Find the index of the series in the watchedSeries vector
    auto it = find(watchedSeries.begin(), watchedSeries.end(), series);
    if (it != watchedSeries.end()) {
        // Calculate the index of the series
        int index = distance(watchedSeries.begin(), it);

        // Check if the series has more episodes than the episodes watched
        vector <int> episodesperseason = series->getEpisodesPerSeason(); 
        int totalepisodes = 0;
        for (auto it = episodesperseason.begin(); it!=episodesperseason.end(); it++){
            totalepisodes += *it;
        }
        //cout << "Total episodes: " << totalepisodes;

        // ! Check if total episodes is smaller
        if (n > 0) {
            episodesWatched[index] = min(totalepisodes, n); // Update to the minimum of n or total episodes
        } else {
            // Increment the number of episodes watched by 1 if it's less than the total episodes
            if (episodesWatched[index] < totalepisodes) {
                episodesWatched[index]++;
            }
        }
        return 0;
    } else {
        cout << "Error: Series not found in watched series." << endl;
        return -2;
    }
}

void User::displayUserInfo(ostream& os) const
{
    os << "Displaying user info:" << endl;
    os << "-----Username: " << username << endl;
    os << "-----Name: " << name << endl;
    os << "-----Country: " << country << endl;
    os << "-----Favorite Genres:" << endl;
    for (auto ir = favoriteGenres.begin(); ir != favoriteGenres.end(); ++ir){
        os << "------ " << *ir << endl;
    }
    os << "-----Watched Series:" << endl;
    for (size_t i = 0; i < watchedSeries.size(); ++i) {
        os << "------ " << watchedSeries[i]->getTitle() << ", Episodes Watched: " << episodesWatched[i] << endl;
    }
    cout << endl;
}

int User::addRating(TVSeries* series, float rating)
{
   // Check if the series pointer is valid
    if (series == nullptr) {
       // cout << "Error: Invalid series pointer." << endl;
        return -1; // Return -1 to indicate an error
    }

    // Find the index of the series in the watchedSeries vector
    auto it = find(watchedSeries.begin(), watchedSeries.end(), series);
    if (it != watchedSeries.end()) {
        // Calculate the index of the series
        size_t index = distance(watchedSeries.begin(), it);

        // Check if the rating vector has enough space
        if (index >= this->ratings.size()) {
            // Resize the rating vector to accommodate the new rating
            this->ratings.resize(index + 1, 0);
        }

        // Add the rating to the corresponding index
        this->ratings[index] = rating;
        return 0; // Successfully added rating
    } else {
       // cout << "Error: Series not found in watched series." << endl;
        return -2; // Return -1 to indicate series not found
    } 
}


int User::numberOfEpisodesToSee(string title, list<TVSeries*> listTVSeries )
{
    if((title.empty())|| listTVSeries.empty())
    {
        return -1;
    }
    int total=0;
    queue<TVSeries*> aux;
    vector<int> nepisodes;
    int n=wishSeries.size();
    bool exist=false;
    for (int i=0;i<n;i++)
    {
        
        if(wishSeries.front()->getTitle()==title)
        {
        exist=true;
        break;
        }
        aux.push(wishSeries.front());
        nepisodes=wishSeries.front()->getEpisodesPerSeason();
        for (int j=0;j<(int)nepisodes.size();j++)
        {
          total+=nepisodes[j];
        }
        wishSeries.pop();
    }
    while(!wishSeries.empty())
    {
        aux.push(wishSeries.front());
        wishSeries.pop();
    }
    while(!aux.empty())
    {
        wishSeries.push(aux.front());
        aux.pop();
    }
    if (!exist) total=0;
    return total;
}

// implementation of class TVSeriesManagement

TVSeriesManagement::TVSeriesManagement(){};

vector<TVSeries*> TVSeriesManagement::getVectorTVSeries() const { return vectorTVSeries; }

int TVSeriesManagement::TVSeriesDelete(string title)
{
    for (auto it = vectorTVSeries.begin(); it != vectorTVSeries.end(); ++it) {
        if ((*it)->getTitle() == title) {
            delete *it; // Free the memory allocated for the TVSerie object
            vectorTVSeries.erase(it); // Remove the pointer from the vector
            return 0; // Series deleted successfully
        }
    }
    return -1; // Series not found
}



int TVSeriesManagement::TVSeriesInsert(TVSeries* series)
{
    // Check if the series pointer is valid
    if (series == nullptr) {
        cout << "Error: Invalid series pointer." << endl;
        return -1; // Return -1 to indicate an error
    }
  if (vectorTVSeries.size()==0)
  {
    vectorTVSeries.push_back(series);
    return 0;
  }
    auto it = find(vectorTVSeries.begin(), vectorTVSeries.end(), series);


    if (it == vectorTVSeries.end()) {
        vectorTVSeries.push_back(series);
      
        return 0;
    } else { return 1;}

    return -1; // Series not found
}


// implementation of class UserManagement

UserManagement::UserManagement(){};

vector<User*> UserManagement::getVectorUsers() const { return vectorUsers; }

void UserManagement::addUser(User* newUser)
{
    vectorUsers.push_back(newUser);
}

int UserManagement::updateWatched(string filename, TVSeriesManagementList& manager)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return -1;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string seriesName, username,eps;
        int episodesSeen;
        getline(ss, seriesName, ',');
        getline(ss, username, ',');
        getline(ss, eps, ',');
        episodesSeen = stoi(eps);
       // cout << seriesName << username << episodesSeen << endl;

        // Check if user exists, if not, create and add to vectorUser
        User* userPtr = nullptr;
        for (User* user : vectorUsers) {
            if (user->getUsername() == username) {
                userPtr = user;
                break;
            }
        }
        if (userPtr == nullptr) {
            // User does not exist, create and add to vectorUser
            vectorUsers.push_back(new User(username, "Unknown", "Unknown", {}));
            userPtr = vectorUsers.back();
        }
        // Check if the series exists
        bool seriesExists = false;
        for (const auto& seriesPtr : manager.getListTVSeries()) {
            
            if (seriesPtr->getTitle() == seriesName) {
                seriesExists = true;
                //add series to user. 
                userPtr->addWatchedSeries(seriesPtr);
                userPtr->addEpisodesWatched(seriesPtr, episodesSeen);
            }
        }

        if (!seriesExists) {
            cout << "TV series does not exist so it wasn't added to the user." << endl;
            continue;
        }
    }
    file.close();
    return 0;
}

// implementation of class TVSeriesManagementList

TVSeriesManagementList::TVSeriesManagementList(){};

list<TVSeries*> TVSeriesManagementList::getListTVSeries() const { return listTVSeries; }

int TVSeriesManagementList::TVSeriesInsert(TVSeries* series)
{
    // Check if the series pointer is valid
    if (series == nullptr) {
        cout << "Error: Invalid series pointer." << endl;
        return -1; // Return -1 to indicate an error
    }
  if (listTVSeries.size()==0)
  {
    listTVSeries.push_back(series);
    return 0;
  }
    auto it = find(listTVSeries.begin(), listTVSeries.end(), series);


    if (it == listTVSeries.end()) {
        listTVSeries.push_back(series);
      
        return 0;
    } else { return 1;}

    return -1; // Series not found
}

list<TVSeries*> TVSeriesManagementList::seriesByCategory(string cat) const
{
  list<TVSeries*> ltv;
  if (cat.empty())
  return ltv;
  for( auto it=listTVSeries.begin();it!=listTVSeries.end();it++)
  {
 
    if ((*it)->getGenre()==cat)
    ltv.push_back((*it));
  }
  return ltv;

}


int TVSeriesManagementList::TVSeriesDelete(string title, UserManagementList& userManagementlist)
{
    if (title.empty())
    return -1;
    int nUser=0,nWatched=0;
    list<User*> listUsers=userManagementlist.getListUsers();
   // vector<TVSeries*>& watechedSeries;
    for(auto it=listTVSeries.begin();it!=listTVSeries.end();it++)
    {
        if ((*it)->getTitle()==title)
        {
            nUser=listUsers.size();
            for (auto itU=listUsers.begin();itU!=listUsers.end();itU++)
            {
                vector<TVSeries*>& watechedSeries=(*itU)->getWatchedSeries();
                nWatched=watechedSeries.size();
                for (int i=0; i<nWatched;i++)
                {
                    cout << watechedSeries[i]->getTitle()<<endl;
                    if(watechedSeries[i]->getTitle()==title)
                    {
                        
                        watechedSeries.erase(watechedSeries.begin()+i);
                        
                        vector<int>& vepisodes=(*itU)->getEpisodesWatched();
                        vepisodes.erase(vepisodes.begin()+i);
                        vector<int>& vrating=(*itU)->getRatings();
                        vrating.erase(vrating.begin()+i);
                    }
                }
            }
            delete(*it);
            listTVSeries.erase(it);
            return 0;
        }
    }
    return -1;
}

// implementation of class UserManagementList

UserManagementList::UserManagementList(){};

list<User*> UserManagementList::getListUsers() const { return listUsers; }

void UserManagementList::addUser(User* newUser)
{
    listUsers.push_back(newUser);
}

list<User*> UserManagementList::seeAll(TVSeries* series)
{
    list<User*> lUser;
    if (series==nullptr)
    {
        return lUser;
    }
    vector<TVSeries*> vWateched;
    vector<int> vepisodes;
    int total=0;
    vector<int> nepisodes;
    nepisodes=series->getEpisodesPerSeason();
    for (int j=0;j<(int)nepisodes.size();j++)
    {
        total+=nepisodes[j];
    }
    for(auto it=listUsers.begin();it!=listUsers.end();it++)
    {
        vWateched=(*it)->getWatchedSeries();
        for (int i=0;i<(int)vWateched.size();i++)
        {
            if ((vWateched[i]==series) && ((*it)->getEpisodesWatched()[i]==total))
            {
                lUser.push_back(*it);

            }
        }
    }
    return lUser;
}

list<TVSeries*> TVSeriesManagementList::suggestsSeries(string username,string userWhoSuggests, list<User*> userlist ) const
{
    list<TVSeries*> lTVSeries;
    if (username.empty()|| userlist.empty() )
    {
        return lTVSeries;
    }
    bool exist=false;
    auto itU=userlist.begin();
    for (itU=userlist.begin();itU!=userlist.end();itU++)
    {
        if((*itU)->getUsername()==username)
        {exist=true;
        break;}
    }
 
     
    if (!exist)
    {
        return lTVSeries;
    }
   vector<string> vcatU=(*itU)->getFavoriteGenres();
    vector<TVSeries*> vTVSeries=(*itU)->getWatchedSeries();
    vector<TVSeries*> vWhoTVSeries;
    exist=false;
    auto itWho=userlist.begin();
for (itWho=userlist.begin();itWho!=userlist.end();itWho++)
    {
        if((*itWho)->getUsername()==userWhoSuggests)
        {exist=true;
        break;}
    }

    if (!exist)
    {
        for(auto it=listTVSeries.begin();it!=listTVSeries.end();it++)
        {
            if ((find(vTVSeries.begin(),vTVSeries.end(),*it)==vTVSeries.end()) && (find(vcatU.begin(),vcatU.end(),(*it)->getGenre())!=vcatU.end()))
            {
                lTVSeries.push_back(*it);
            }
        }
    } else
    {
        vWhoTVSeries=(*itWho)->getWatchedSeries();
          for(auto it=vWhoTVSeries.begin();it!=vWhoTVSeries.end();it++)
        {
            if ((find(vTVSeries.begin(),vTVSeries.end(),*it)==vTVSeries.end()) && (find(vcatU.begin(),vcatU.end(),(*it)->getGenre())!=vcatU.end()))
            {
                lTVSeries.push_back(*it);
            }
        }
    }
   
    return lTVSeries;
}


// implementation of class NodeUser
NodeUser::NodeUser(User* user){
    this->user=user;
    left=nullptr;
    right=nullptr;
} 

// implementation of class UserManagementTree
UserManagementTree::UserManagementTree() {
    root=nullptr;
}

NodeUser* UserManagementTree::insertNode(NodeUser* root, User* newUser) {
        // If the tree is empty, create a new node and return it
        if (root == nullptr) {
            return new NodeUser(newUser);
        }

        // Compares username to decide where to insert the node
        if (newUser->getUsername() < root->user->getUsername()) {
            root->left = insertNode(root->left, newUser);
        } else if (newUser->getUsername() > root->user->getUsername()) {
            root->right = insertNode(root->right, newUser);
        }

        return root;
    }
    
NodeUser* UserManagementTree::findMinNode(NodeUser* node) {
    NodeUser* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
    }

NodeUser* UserManagementTree::deleteNode(NodeUser* root, string user) {
    // Base case: empty tree
    if (root == nullptr) {
        return root;
    }

    // If the username to be deleted is smaller than the username of the current node, search the left subtree
    if (user < root->user->getUsername()) {
        root->left = deleteNode(root->left, user);
    }
    // If the username to be deleted is greater than the username of the current node, search the right subtree
    else if (user > root->user->getUsername()) {
        root->right = deleteNode(root->right, user);
    }
    // If the user is the same as the year of the current node, this is the node to be deleted
       else {
        // Case 1: node without children or with only one child
        if (root->left == nullptr) {
                NodeUser* temp = root->right;
                delete root;
                return temp;
        } else if (root->right == nullptr) {
                NodeUser* temp = root->left;
                delete root;
                return temp;
            }

        // Case 2: node with two children
        // Finds the minimum node of the right subtree (the successor)
        NodeUser* temp = findMinNode(root->right);
        // Copy successor to this node
        root->user = temp->user;
        // Exclui o sucessor
        root->right = deleteNode(root->right, temp->user->getUsername());
        }
    return root;
}

void UserManagementTree::inorderTraversal(NodeUser* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->user->getUsername() << " " << root->user->getName() << endl;
        inorderTraversal(root->right);
    }
}

NodeUser* UserManagementTree::getRoot() const
{
    return root;
}

void UserManagementTree::addUser(User* newUser) {
    root = insertNode(root, newUser);
}

void UserManagementTree::remove(string user) {
        root = deleteNode(root, user);
    }

void UserManagementTree::inorder() {
        inorderTraversal(root);
    }







/**************************/
/*     A implementar      */
/**************************/







priority_queue<TVSeries> UserManagement::queueTVSeriesCategory(priority_queue<TVSeries>& pq, string cat)
{
    priority_queue <TVSeries> macaco = pq;
    priority_queue <TVSeries> manke;
    bool ValidCat = false;
    for(int i=0; i < (N_GENRES-1); i++)
    {
        //Verifica se o género "cat" corresponde a algum dos géneros existentes
        if(cat == vGenres[i])
        {
            //Caso corresponda então é um género válido e "ValidCat" passa a ter valor "true"
            ValidCat = true;
        }
    }
    if(ValidCat == false)
    {
        return manke; //Notar que ainda não foi adicionado qualquer elemento à lista 
    }



    
    while(!macaco.empty())
    {
        if(macaco.top().getGenre() == cat)
        {
            manke.push(macaco.top());
        }
        macaco.pop();
    }
    return manke;
    
  //answer here
}







priority_queue<TVSeries> UserManagement::queueTVSeries(list<TVSeries*> listTV,int min)
{
    list<TVSeries*> rogerio = listTV;
    priority_queue <TVSeries> alex;

    if(min <= 0) return alex;
    for(auto serie : rogerio)
    {
        if(serie == nullptr) return alex;
    }
    while(!rogerio.empty())
    {
        int persona = 0;
        for(auto Ishigod = vectorUsers.begin(); Ishigod != vectorUsers.end(); Ishigod++)
        {
            auto chika = ((*Ishigod)->getWatchedSeries());
            for(size_t i = 0; i < chika.size(); i++)
            {
            
                    if( chika[i]->getTitle() == rogerio.front()->getTitle())
                    {
                        if((*Ishigod)->getEpisodesWatched()[i] >= 2)
                        {
                            persona++;
                        }
                    }
            }
        }
        if(persona >= min)
        {
            alex.push(*rogerio.front());
        }
        rogerio.pop_front();
    }
    return alex;
    //answer here
}







vector<User*> UserManagementTree::usersInitialLetter(NodeUser* root,char ch)
{
    vector<User*> UserLet;
    
    if(root == nullptr)
    {
        return UserLet;
    }
    
    if((ch < 65 || ch > 90) && (ch < 97 || ch > 122))
    {
        return UserLet;
    }

    if(root->user->getUsername()[0] == ch || root->user->getUsername()[0] == (ch + 32) || root->user->getUsername()[0] == (ch - 32))
    {
        UserLet.push_back(root->user);
    }

    vector<User*> KarlMarx = usersInitialLetter(root->left, ch);
    vector<User*> Adolfo = usersInitialLetter(root->right, ch);
    
    UserLet.insert(UserLet.end(), KarlMarx.begin(), KarlMarx.end());
    UserLet.insert(UserLet.end(), Adolfo.begin(), Adolfo.end());


    return UserLet;
  //answer here
    
  //answer here
}







list<User*> UserManagementTree::usersNotFan(NodeUser* root)
{
    list<User*> ChicoAmaro;
    int luffy = 0;
    int charlotte = 0;
    
    if(root == nullptr)
    {
        return ChicoAmaro;
    }
    auto notNarutoKaguya = root->user->getWatchedSeries();

    for(size_t ShiroganeSenpai = 0; ShiroganeSenpai < notNarutoKaguya.size(); ShiroganeSenpai++)
    {
        for(int backshot = 0; backshot < notNarutoKaguya[ShiroganeSenpai]->getNumberOfSeasons(); backshot++)
        {
            luffy += notNarutoKaguya[ShiroganeSenpai]->getEpisodesPerSeason()[backshot];
        }
        if(root->user->getEpisodesWatched()[ShiroganeSenpai] < luffy)
        {
            charlotte++;
        }

        luffy = 0;
    }
    if(charlotte > 2)
    {
        ChicoAmaro.push_back(root->user);
    }
    
    list<User*> McQueen = usersNotFan(root->left);
    list<User*> Kitler = usersNotFan(root->right);
    
    ChicoAmaro.insert(ChicoAmaro.end(), McQueen.begin(), McQueen.end());
    ChicoAmaro.insert(ChicoAmaro.end(), Kitler.begin(), Kitler.end());
    
    return ChicoAmaro;
    
  //answer here
}







vector<int> UserManagementTree::usersCategoryStatistics(NodeUser* root,string cat,int perc)
{
    vector<int> sandro{0,0,0};
    //vector<int> usopp{6,4,1};
    vector<int> usopp;
    int jesus = 0, maria = 0, jose = 0, roberto = 0, backbending = 0;
    bool trustMeBro = false, frizeLimao = false, panoDeLimparOPo = false, ValidCat = false;
    
    if( root == nullptr || perc <= 0 || perc > 100 )
    {
        return sandro;
    }
    
    auto deusComMaiuscula = root->user->getWatchedSeries();
    auto aguaDeSaoMartinho = root->user->getFavoriteGenres();
    auto barbie = root->user->getEpisodesWatched();
    
    for(int i=0; i < (N_GENRES-1); i++)
    {
        //Verifica se o género "cat" corresponde a algum dos géneros existentes
        if(cat == vGenres[i])
        {
            //Caso corresponda então é um género válido e "ValidCat" passa a ter valor "true"
            ValidCat = true;
        }
    }
    if(ValidCat == false)
    {
        return sandro; //Notar que ainda não foi adicionado qualquer elemento à lista 
    }
    
    for(size_t alpha = 0; alpha < deusComMaiuscula.size(); alpha++)
    {
        if(deusComMaiuscula[alpha]->getGenre() == cat)
        {
            panoDeLimparOPo = true;
            
            for(int sokka = 0; sokka < deusComMaiuscula[alpha]->getNumberOfSeasons(); sokka++)
            {
                backbending += deusComMaiuscula[alpha]->getEpisodesPerSeason()[sokka];
            }
            
            roberto = ((backbending * perc)/100);
            backbending = 0;
            if(barbie[alpha] >= roberto)
            {
                frizeLimao = true;
                for(size_t ishowthemeat = 0; ishowthemeat < aguaDeSaoMartinho.size(); ishowthemeat++)
                {
                    if(aguaDeSaoMartinho[ishowthemeat] == cat)
                    {
                        trustMeBro = true;
                    }
                }
            }
        }
    }
    if(panoDeLimparOPo == true) jesus++;
    
    if(frizeLimao == true) maria++;
    
    if(trustMeBro == true) jose++;

    
    usopp.push_back(jesus);
    usopp.push_back(maria);
    usopp.push_back(jose);
    

    vector<int> maisUmCromossoma = usersCategoryStatistics(root->left, cat, perc); 
    
    if(maisUmCromossoma != sandro)
    {
        usopp[0] += maisUmCromossoma[0];                          
        usopp[1] += maisUmCromossoma[1];
        usopp[2] += maisUmCromossoma[2];
    }
    
    vector<int> menosUmCromossoma = usersCategoryStatistics(root->right, cat, perc);
    
    if(menosUmCromossoma != sandro)
    {
        usopp[0] += menosUmCromossoma[0];                          
        usopp[1] += menosUmCromossoma[1];
        usopp[2] += menosUmCromossoma[2];
    }
    
    //usopp.push_back(jesus);
    //usopp.push_back(maria);
    //usopp.push_back(jose);
    
    
    return usopp;
  //answer here
}
