import ijson
import folium

locations = []

with open("../data/ebird_response.json", 'r') as f:
    # Stream each item (hotspot) in the top-level JSON array
    objects = ijson.items(f, 'item')
    count = 0
    for obj in objects:
        lat = obj.get("lat")
        lng = obj.get("lng")
        numSpeciesAllTime = obj.get("numSpeciesAllTime")
        locName = obj.get("locName")
        locations.append((lat, lng, numSpeciesAllTime, locName))
        count += 1
        if count <= 3:
            print(obj)  # print first 3 for sanity check

print(f"Loaded {count} hotspots")

# Center map at average lat/lng
avg_lat = sum(lat for lat, _, _, _ in locations) / len(locations)
avg_lng = sum(lng for _, lng, _, _ in locations) / len(locations)
m = folium.Map(location=[avg_lat, avg_lng], zoom_start=12)

# Add each location as a blue marker with tooltip showing species count and name
for lat, lng, numSpeciesAllTime, locName in locations:
    tooltip_text = f"{locName} ({numSpeciesAllTime} species)"
    folium.CircleMarker(
        location=[lat, lng], 
        radius=5, 
        color="blue", 
        fill=True,
        tooltip=tooltip_text
    ).add_to(m)

# Save to HTML
m.save("ebird_hotspots_map.html")
print("Map saved to ebird_hotspots_map.html. Open in your browser to view.")
