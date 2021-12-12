using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace day12
{
    public class Connection {
        public string start, end;

        public Connection(string b, string e) {
            start = b; end = e;
        }
    }

    public class Node {
        public List<Node> children;
        public string name;
        public bool isTwice;

        public Node(string name, bool twice = false) {
            this.name = name;
            this.isTwice = twice;
            children = new List<Node>();
        }

        public bool IsSmall() { foreach(char c in name) if (!Char.IsLower(c)) return false; return true; }
    }

    public class Program
    {
        static string PathUID(Stack<Node> path) {
            StringBuilder builder = new StringBuilder();
            
            Stack<Node> tmp = new Stack<Node>();
            while (path.Count > 0) {
                var temp = path.Pop();
                builder.Insert(0, temp.name + ",", 1);
                tmp.Push(temp);
            }

            while(tmp.Count > 0) path.Push(tmp.Pop());

            return builder.ToString();
        }

        static void Path(Node current, Stack<Node> path, HashSet<string> paths) {
            if(current.name == "end") {
                paths.Add(PathUID(path));
                return;
            }

            path.Push(current);
            foreach (var node in current.children) {
                if(node == path.Peek()) {
                    continue;
                }

                if(node.IsSmall() && path.Where((n) => n == node).Count() >= (node.isTwice ? 2 : 1)) {
                    continue;
                }

                Path(node, path, paths);
            }
            path.Pop();
        }

        static void Main(string[] args)
        {
            // Parse line
            var file = File.OpenText("main.txt");
            string line;
            var connections = new List<Connection>();
         
            while((line = file.ReadLine()) != null) {
                string[] be = line.Split('-');
                
                connections.Add(new Connection(be[0], be[1]));
            }

            // Build map
            var nodes = new Dictionary<string, Node>();
            foreach(var connection in connections) {
                if (!nodes.ContainsKey(connection.start)) nodes.Add(connection.start, new Node(connection.start));
                if (!nodes.ContainsKey(connection.end)) nodes.Add(connection.end, new Node(connection.end));

                nodes[connection.start].children.Add(nodes[connection.end]);
                nodes[connection.end].children.Add(nodes[connection.start]);
            }


            // Part 1
            var start = nodes["start"];
            var uniquePaths = new HashSet<string>();
            Path(start, new Stack<Node>(), uniquePaths);

            Console.WriteLine("Part 1: {0} paths", uniquePaths.Count());            

            // Part 2
            uniquePaths.Clear();
            foreach (var _node in nodes.Values.Where((n) => n.IsSmall() && n.name != "start")) {
                foreach(var node in nodes.Values) {
                    node.isTwice = _node == node;
                }

                Path(start, new Stack<Node>(), uniquePaths);
            }

            Console.WriteLine("Part 2: {0} paths", uniquePaths.Count());
        }
    }
}
