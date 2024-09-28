use std::fmt::Display;

/// A tree node
struct Node<T: Ord + Display> {
    /// The element this node represents
    elem: T,

    /// A pointer to the left tree, if it exists
    left: Option<Box<Node<T>>>,

    /// A pointer to the right tree, if it exists
    right: Option<Box<Node<T>>>,
}

/// A BST representation.
struct BST<T: Ord + Display> {
    /// The root node of the tree, if it exists.
    root: Option<Node<T>>,
}

/// Implementation of the actual Node methods (add, delete, contains, ...)
impl<T: Ord + Display> Node<T> {
    /// Creates a leaf node
    fn new(elem: T) -> Node<T> {
        Node {
            elem,
            left: None,
            right: None,
        }
    }

    /// This method adds a new element to the node element.
    ///
    /// If the element is ultimately added, then true is returned. If the
    /// tree doesn't change, false is returned.
    fn add(self: &mut Self, elem: T) -> bool {
        // Compare our element with the new element
        match elem.cmp(&self.elem) {
            // For each comparison, map to which branch we need to compare
            // next, if applicable.
            std::cmp::Ordering::Equal => None,
            std::cmp::Ordering::Less => Some(&mut self.left),
            std::cmp::Ordering::Greater => Some(&mut self.right),
        }
        // Now, if we have a branch, then we need to add the value to
        // that node
        .map(|node| match node {
            Some(branch) => branch.add(elem),
            // Unless the branch doesn't exist. In that case, we need to
            // create it.
            None => {
                *node = Some(Box::new(Node::new(elem)));
                true
            }
        })
        // When we reach here, we either have None, which means the element
        // is equal to our element (we want to return false), or we have
        // Some(bool). In which case, we want to return the boolean contained
        // in this Some() value.
        .map_or(false, |x| x)
    }
}

/// Implementation of the actual BST methods (add, delete, etc xD)
impl<T: Ord + Display> BST<T> {
    /// Creates a new BST
    fn new() -> BST<T> {
        BST { root: None }
    }

    /// Adds a new element to the BST
    fn add(&mut self, elem: T) -> bool {
        match &mut self.root {
            // If the root exists, add the value to the node
            Some(root) => root.add(elem),
            // Otherwise, create the root element
            None => {
                self.root = Some(Node::new(elem));
                true
            }
        }
    }
}

/// Custom trait to represent when a type can be converted into a graphviz
/// graph or not.
trait GraphVizOperator {
    /// Returns a string with the graphviz representation.
    fn to_graphviz_str(&self) -> String;
}

/// Implementation of the GraphVizOperator Trait for Node
impl<T: Ord + Display> GraphVizOperator for Node<T> {
    fn to_graphviz_str(&self) -> String {
        let mut result = format!("\tn{};\n", self.elem);
        let mut print_node = |node: &Box<Node<T>>| {
            result.push_str(&format!("\tn{} -- n{};\n", self.elem, (*node).elem));
            result.push_str(&node.to_graphviz_str());
        };
        self.left.as_ref().map(&mut print_node);
        self.right.as_ref().map(&mut print_node);
        result
    }
}

/// Implementation of the GraphVizOperator Trait for BST
impl<T: Ord + Display> GraphVizOperator for BST<T> {
    fn to_graphviz_str(&self) -> String {
        let inner_str: String = self
            .root
            .as_ref()
            .map(|x| x.to_graphviz_str())
            .unwrap_or(String::from(""));
        format!("strict graph BST {{\n{inner_str}}}\n")
    }
}

fn main() {
    let mut bst = BST::new();

    bst.add(10);
    bst.add(5);
    bst.add(7);
    bst.add(15);
    bst.add(17);
    bst.add(1);
    bst.add(13);

    println!("{}", bst.to_graphviz_str());
}
