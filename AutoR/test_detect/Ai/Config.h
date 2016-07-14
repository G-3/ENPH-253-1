
namespace Config{
    namespace Board{ 
        // links describes edges between nodes: dest, start, dir from start to dest
        // dir-> 0:R 1:T 2:L 3:B
        const int links[2][3] = {{1, 0, 1},{1, 2, 0}};
        const int linksSize = 2;
    }
}
