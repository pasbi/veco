import ommpfritt as o

root = o.scene.root
root.props["name"] = "A" if root.props["name"] == "B" else "B"

scripttag = o.this;
print(scripttag.props[code]) # quine
print(scripttag.owner.props["name"])


