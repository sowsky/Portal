//#pragma once
//#include <SFML/Graphics.hpp>
//#include <memory>
//#include "Const.h"
//#pragma warning(disable:4996)
//using namespace sf;
//
//struct Light
//{
//    Light(sf::Vector3f col, sf::Vector3f pos, sf::Vector3f att) : color(col),
//        position(pos),
//        attenuation(att)
//    {
//    }
//    sf::Vector3f color;
//    sf::Vector3f position;
//    sf::Vector3f attenuation;
//};
//
//class Shader
//{
//};
//
//const int width = WINDOW_WIDTH;
//const int height = WINDOW_HEIGHT;
//
//int main()
//{
//    sf::RenderWindow window({ width, height }, "Dynamic Lighting Test");
//
//    // Front and backbuffer as Pointer for std::swap
//    std::unique_ptr<sf::RenderTexture> front, back;
//    sf::RenderTexture pass_normals, pass_diffuse;
//    sf::Texture normal_map, diffuse_map;
//
//    front = std::unique_ptr<sf::RenderTexture>(new sf::RenderTexture());
//    back = std::unique_ptr<sf::RenderTexture>(new sf::RenderTexture());
//
//    front->create(width, height);
//    back->create(width, height);
//
//    pass_normals.create(width, height);
//    pass_diffuse.create(width, height);
//
//    normal_map.loadFromFile("graphics/1.png");
//    diffuse_map.loadFromFile("graphics/2.png");
//
//    sf::Sprite sprite(diffuse_map);
//
//    sf::Shader lights_shader;
//    sf::Shader normals_shader;
//
//    // Add a "warm" light, color needs to be in 0 - 1 range
//    Light light(sf::Vector3f(255 / 255.0, 214 / 255.0, 170 / 255.0),
//        sf::Vector3f(0, 0, 0.02),
//        sf::Vector3f(0.5, 0.5, 0.5));
//
//
//    lights_shader.loadFromFile("shader/light.frag", sf::Shader::Fragment);
//    normals_shader.loadFromFile("shader/normals.frag", sf::Shader::Fragment);
//
//    // Center Sprite
//    sprite.setOrigin(150.0f, 112.5f);
//    //sprite.setPosition(400, 300);
//
//    Vector2u texSize = sprite.getTexture()->getSize();
//    sprite.setOrigin((Vector2f)texSize * 0.5f);
//    sprite.setPosition(window.getView().getCenter());
//    sprite.setScale(0.5f, 0.5f);
//
//    // Environmental variables
//    float ambient_intensity = 0.7;
//    sf::Vector3f falloff(0.5, 0.5, 0.5);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed) window.close();
//
//            // controls for environment
//            // mousewheel to control height of the controlled light
//            // + and - to control ambient light intensity
//            // x and y to control controlled light falloff
//            if (event.type == sf::Event::MouseWheelMoved)
//            {
//                light.position.z += event.mouseWheel.delta * 0.01;
//            }
//
//            if (event.type == sf::Event::KeyPressed)
//            {
//                if (event.key.code == sf::Keyboard::Add)
//                {
//                    ambient_intensity += 0.05f;
//                }
//                if (event.key.code == sf::Keyboard::Subtract)
//                {
//                    ambient_intensity -= 0.05f;
//                }
//                if (event.key.code == sf::Keyboard::Y)
//                {
//                    falloff /= 0.5f;
//                }
//                if (event.key.code == sf::Keyboard::X)
//                {
//                    falloff *= 0.5f;
//                }
//            }
//        }
//
//        window.clear();
//        // Clear renderbuffers
//        back->clear();
//        front->clear();
//        pass_diffuse.clear();
//        // Set normals buffer to neutral color
//        pass_normals.clear(sf::Color(128, 128, 255));
//
//        // set light position, and adjust for different coordinate systems
//        light.position.x = sf::Mouse::getPosition(window).x;
//        light.position.y = height - sf::Mouse::getPosition(window).y;
//
//        // Diffuse Pass, feed every sprite to draw here before display
//        pass_diffuse.draw(sprite);
//        pass_diffuse.display();
//
//        // Normals Pass, feed every normal map which should be rendered here
//        // For more then one repeat the next 2 steps before displaying
//        normals_shader.setParameter("sampler_normal", normal_map);
//        pass_normals.draw(sprite, &normals_shader);
//        pass_normals.display();
//
//        // Light Pass, renders every light into a rendertexture
//        lights_shader.setParameter("resolution", sf::Vector2f(width, height));
//        lights_shader.setParameter("sampler_normal", pass_normals.getTexture());
//        lights_shader.setParameter("ambient_intensity", ambient_intensity);
//        lights_shader.setParameter("falloff", falloff);
//
//        // For more lights put the next 6 lines into a loop
//        lights_shader.setParameter("sampler_light", front->getTexture());
//        lights_shader.setParameter("light_pos", light.position);
//        lights_shader.setParameter("light_color", light.color);
//        back->draw(sf::Sprite(pass_diffuse.getTexture()), &lights_shader);
//        back->display();
//        std::swap(back, front);
//
//        // Draw diffuse color
//        window.draw(sf::Sprite(pass_diffuse.getTexture()));
//        // Blend lighting over
//        window.draw(sf::Sprite(front->getTexture()), sf::BlendMultiply);
//        // Finally display it
//        window.display();
//    }
//
//    return 0;
//}