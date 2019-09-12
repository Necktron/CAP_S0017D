//
//  GameScene.swift
//  DeDebugger
//
//  Created by sdev on 23/10/18.
//  Copyright © 2018 sdev. All rights reserved.
//

import SpriteKit
import GameplayKit
import UIKit

class GameScene: SKScene
{
    //var startButton: SKSpriteNode
    
    struct ObjectOnScreen
    {
        var currentX: CGFloat
        var currentY: CGFloat
        var TheBug: SKSpriteNode
    }

    var possibleBugs = ["ANT", "BUTTERFLYTWO", "BEE", "LADYBUG", "BUTTERFLY"]


    var ListOfBugs = [ObjectOnScreen]()
    
    var gameActive = false
    var menuActive = true
    var victory = false
    
    var scorePoints = 0

    var victoryBG = SKSpriteNode()
    var logo = SKSpriteNode()
    var playText = SKLabelNode()
    var gameTitleLabel = SKLabelNode()
    var victoryLabel = SKLabelNode()
    var scoreLabel = SKLabelNode()
    
    //var gameTimer:Timer!
    
    func LoadMainMenu()
    {
        let game = GameScene(fileNamed: "MainMenu")
        game?.scaleMode = .aspectFill
        view!.presentScene(game!, transition: SKTransition.fade(withDuration: 0.5))
        //gameActive = false
    }
    
    func LoadGame()
    {
        let game = GameScene(fileNamed: "GameScene")
        game?.scaleMode = .aspectFill
        view!.presentScene(game!, transition: SKTransition.fade(withDuration: 0.5))
    }
    
    override func didMove(to view: SKView)
    {
        if let playTextRef = self.childNode(withName: "//PlayText") as? SKLabelNode
        {
            playText = playTextRef
        }
        
        if let gameTitleLabelRef = self.childNode(withName: "//GameTitleLable") as? SKLabelNode
        {
            gameTitleLabel = gameTitleLabelRef
        }
        
        if let victoryBGRef = self.childNode(withName: "//VictoryBG") as? SKSpriteNode
        {
            victoryBG = victoryBGRef
        }
        
        if let victoryLabelRef = self.childNode(withName: "//VictoryLable") as? SKLabelNode
        {
            victoryLabel = victoryLabelRef
        }
        
        if let scoreLabelRef = self.childNode(withName: "//Score") as? SKLabelNode
        {
            scoreLabel = scoreLabelRef
        }
        
        if let logoRef = self.childNode(withName: "//Logo") as? SKSpriteNode
        {
            logo = logoRef
        }
        
        victoryBG.alpha = 0
        victoryLabel.alpha = 0
        scoreLabel.alpha = 0
        
        self.scaleMode = .aspectFit
        let border = SKPhysicsBody(edgeLoopFrom: self.frame)
        
        border.friction = 0
        border.restitution = 1
        
        self.physicsBody = border
        
        for index in 1...5
        {
            AddBug(BugName: "ANT")
        }
        for index in 1...5
        {
            AddBug(BugName: "BUTTERFLYTWO")
        }
        for index in 1...5
        {
            AddBug(BugName: "BEE")
        }
        for index in 1...5
        {
            AddBug(BugName: "BUTTERFLY")
        }
        for index in 1...5
        {
            AddBug(BugName: "LADYBUG")
        }
    }

    @objc func AddBug(BugName: String)
    {
        possibleBugs = GKRandomSource.sharedRandom().arrayByShufflingObjects(in: possibleBugs) as! [String]

        let ThisBug = ObjectOnScreen(currentX: 1.0, currentY: 1.0, TheBug: SKSpriteNode(imageNamed: BugName/*possibleBugs[0]*/))

        let randomBugPosX = GKRandomDistribution(lowestValue: -300, highestValue: 300)
        let posX = CGFloat(randomBugPosX.nextInt())

        let randomBugPosY = GKRandomDistribution(lowestValue: -450, highestValue: 450)
        let posY = CGFloat(randomBugPosY.nextInt())

        ThisBug.TheBug.name = BugName
        ThisBug.TheBug.position = CGPoint(x: posX, y: posY)

        self.addChild(ThisBug.TheBug)

        ListOfBugs.append(ThisBug)
    }

    override func update(_ currentTime: TimeInterval)
    {
        // Called before each frame is rendered
        
        //THE GAME ITSELF
        if(gameActive == true && victory == false && menuActive == false)
        {
            let speed: CGFloat = 1.0
            playText.alpha = 0
            gameTitleLabel.alpha = 0
            victoryBG.alpha = 0
            victoryLabel.alpha = 0
            scoreLabel.alpha = 0
            logo.alpha = 0
            
            for index in 0...(ListOfBugs.count - 1)
            {
                    ListOfBugs[index].TheBug.alpha = 1
                    let ShouldChangeDirection = CGFloat(drand48())

                    if ShouldChangeDirection < 0.1
                    {
                        let randDirX = CGFloat(drand48())
                        let randDirY = CGFloat(drand48())

                        if randDirX < 0.3
                        {
                            ListOfBugs[index].currentX *= -1
                        }

                        if randDirY < 0.3
                        {
                            ListOfBugs[index].currentY *= -1
                        }
                    }

                    if (ListOfBugs[index].TheBug.position.x + ListOfBugs[index].currentX * speed >= 300 || ListOfBugs[index].TheBug.position.x + ListOfBugs[index].currentX * speed <= -300)
                    {
                        ListOfBugs[index].currentX *= -1
                    }

                    if (ListOfBugs[index].TheBug.position.y + ListOfBugs[index].currentY * speed >= 450 || ListOfBugs[index].TheBug.position.y + ListOfBugs[index].currentY * speed <= -450)
                    {
                        ListOfBugs[index].currentY *= -1
                    }


                    let moveAction = SKAction.moveBy(x: ListOfBugs[index].currentX * speed, y: ListOfBugs[index].currentY * speed, duration: 0.1)
                    ListOfBugs[index].TheBug.run(moveAction)
            }
        }
        
        //WHILE IN MENU
        if(gameActive == false && victory == false && menuActive == true)
        {
            for index in 0...(ListOfBugs.count - 1)
            {
                ListOfBugs[index].TheBug.alpha = 0
            }
        }
        
        //VICTORY SCREEN
        if(gameActive == false && victory == true && menuActive == false)
        {
            scoreLabel.text = String(scorePoints)
            playText.alpha = 0
            gameTitleLabel.alpha = 0
            victoryBG.alpha = 1
            victoryLabel.alpha = 1
            scoreLabel.alpha = 1
            //logo.alpha = 0
            
            for index in 0...(ListOfBugs.count - 1)
            {
                ListOfBugs[index].TheBug.alpha = 0
            }
            
            victory = false
            
            DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(4), execute: {
                self.LoadMainMenu()
            })
        }
    }

    struct line
    {
        var DrawnLine: SKShapeNode
        var StartPoint: CGPoint
        var EndPoint: CGPoint
    }

    class Player
    {
        var lineNodes : [line] = []
        var master: GameScene
        var Address: Int
        
        init(masterClass: GameScene, hash: Int)
        {
            master = masterClass
            Address = hash
        }
        
        func ClearLines()
        {

            for node in lineNodes
            {
                node.DrawnLine.removeFromParent()
            }

            lineNodes.removeAll(keepingCapacity: false)
        }

        func DrawShape(i: Int)
        {
            let color = UIColor(red: 0.5, green: 0.8, blue: 1.0, alpha: 1.0)
            let path = CGMutablePath()
            var j = i;
            var ListOfPoints : [CGPoint] = []

            if (j == -1)
            {
                j += 1
                path.move(to: lineNodes[j].StartPoint)
                ListOfPoints.append(lineNodes[j].StartPoint)
                path.addLine(to: lineNodes[j].StartPoint)
                ListOfPoints.append(lineNodes[j].EndPoint)

            }

            else
            {
                path.move(to: lineNodes[j].EndPoint)
                ListOfPoints.append(lineNodes[j].EndPoint)
            }

            if ((j+1) < (lineNodes.count-1))
            {
                for index in (j+1)...(lineNodes.count-1)
                {
                    path.addLine(to: lineNodes[index].EndPoint)
                    ListOfPoints.append(lineNodes[index].EndPoint)
                }
            }

            path.closeSubpath()

            let theShape = SKShapeNode(path: path)
            theShape.fillColor = color

            master.addChild(theShape)

            theShape.run(SKAction.sequence([SKAction.fadeAlpha(to: 0, duration: 0.5), SKAction.removeFromParent()
                ]))

            //var ContainedBugs = [ObjectOnScreen]()

            var ContainedBugs = [Int]()

            //var Counter = 0;

            //for Bug in ListOfBugs
            for Bug in 0...(master.ListOfBugs.count - 1)
            {
                if (theShape.contains(master.ListOfBugs[Bug].TheBug.position) && master.ListOfBugs[Bug].TheBug.name != "NULL")
                {
                    ContainedBugs.append(Bug)
                    //ListOfBugs[Bug].TheBug.removeFromParent()
                    //ListOfBugs.remove(at: Bug)

                    //print(Bug)
                    print(master.ListOfBugs[Bug].TheBug.name!)
                }

                //Counter += 1;
            }

            var bugOne = 0
            var bugTwo = 0
            var bugThree = 0
            var bugFour = 0
            var bugFive = 0
            
            print(ContainedBugs.count)
            
            if (ContainedBugs.count > 1)
            {
                var WillClear = true;
                for BugIndex in ContainedBugs
                {
                    if (master.ListOfBugs[ContainedBugs[0]].TheBug.texture!.description != master.ListOfBugs[BugIndex].TheBug.texture!.description)
                    {
                        WillClear = false
                        break
                    }
                }

                if WillClear
                {
                    master.scorePoints += (ContainedBugs.count - 1) * 100
                    //print(master.scorePoints)
                    
                    for Bug in 0...(ContainedBugs.count - 2)
                    {
                        master.ListOfBugs[ContainedBugs[Bug]].TheBug.name = "NULL"
                        master.ListOfBugs[ContainedBugs[Bug]].TheBug.removeFromParent()
                    }
                    
                    for index in 0...(master.ListOfBugs.count - 1)
                    {
                        if (master.ListOfBugs[index].TheBug.name == "ANT")
                        {
                            bugOne += 1
                        }
                            
                        else if (master.ListOfBugs[index].TheBug.name == "BUTTERFLYTWO")
                        {
                            bugTwo += 1
                        }
                            
                        else if (master.ListOfBugs[index].TheBug.name == "BEE")
                        {
                            bugThree += 1
                        }
                            
                        else if (master.ListOfBugs[index].TheBug.name == "BUTTERFLY")
                        {
                            bugFour += 1
                        }
                            
                        else if (master.ListOfBugs[index].TheBug.name == "LADYBUG")
                        {
                            bugFive += 1
                        }
                        
                        if((bugOne <= 1 || bugTwo <= 1 || bugThree <= 1 || bugFour <= 1 || bugFive <= 1) && index == master.ListOfBugs.count - 1)
                        {
                            master.gameActive = false
                            master.victory = true
                            print("VICTORY!!!")
                            master.victoryBG.alpha = 1
                            master.victoryLabel.alpha = 1
                            //master.LoadGame()
                            break
                        }
                    }
                    
                    /*print(bugOne)
                    print(bugTwo)
                    print(bugThree)
                    print(bugFour)
                    print(bugFive)
                    print("")*/
                }
            }
        }

        func FadeOutLine(theLine: line)
        {
            theLine.DrawnLine.run(SKAction.sequence([SKAction.fadeAlpha(to: 0, duration: 1.5), SKAction.removeFromParent()]),
                                  completion:{
                                    if (self.lineNodes.count > 0)
                                    {
                                        self.lineNodes.removeFirst()
                                    }
                                })
        }
    }

    var Players : [Player] = []

    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        if(gameActive == false && menuActive == true && victory == false)
        {
            menuActive = false
            gameActive = true
        }
        
        for t in touches
        {
            let ThisPlayer = Player(masterClass: self, hash: t.hashValue)

            Players.append(ThisPlayer)
        }
    }

    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        var PlayerCounter = 0;

        for t in touches
        {
            for p in 0...(Players.count - 1)
            {
                if (t.hashValue == Players[p].Address)
                {
                    PlayerCounter = p
                    break
                }
            }

            let location = t.location(in: self)
            let previous = t.previousLocation(in: self)

            let path = CGMutablePath()
            path.move(to: location)
            path.addLine(to: previous)

            let theLine = SKShapeNode(path: path)
            theLine.lineWidth = 3
            theLine.strokeColor = .white
            
            let lineStruct = line(DrawnLine: theLine, StartPoint: previous, EndPoint: location)

            self.addChild(lineStruct.DrawnLine)
            Players[PlayerCounter].lineNodes.append(lineStruct)

            var i = 0

            for node in Players[PlayerCounter].lineNodes
            {
                let Ua2: CGFloat = (node.EndPoint.y - node.StartPoint.y) * (lineStruct.EndPoint.x - lineStruct.StartPoint.x) - (node.EndPoint.x - node.StartPoint.x) * (lineStruct.EndPoint.y - lineStruct.StartPoint.y)


                if (Ua2 != 0)
                {
                    let Ua1: CGFloat = (node.EndPoint.x - node.StartPoint.x) * (lineStruct.StartPoint.y - node.StartPoint.y) - (node.EndPoint.y - node.StartPoint.y) * (lineStruct.StartPoint.x - node.StartPoint.x)

                    let xValue: CGFloat = lineStruct.StartPoint.x + (Ua1 / Ua2) * (lineStruct.EndPoint.x - lineStruct.StartPoint.x)


                    let yValue: CGFloat = lineStruct.StartPoint.y + (Ua1 / Ua2) * (lineStruct.EndPoint.y - lineStruct.StartPoint.y)


                    if (((xValue < lineStruct.StartPoint.x && xValue > lineStruct.EndPoint.x) || (xValue > lineStruct.StartPoint.x && xValue < lineStruct.EndPoint.x)) && ((yValue < lineStruct.StartPoint.y && yValue > lineStruct.EndPoint.y) || (yValue > lineStruct.StartPoint.y && yValue < lineStruct.EndPoint.y)))
                    {
                        if (((xValue < node.StartPoint.x && xValue > node.EndPoint.x) || (xValue > node.StartPoint.x && xValue < node.EndPoint.x)) && ((yValue < node.StartPoint.y && yValue > node.EndPoint.y) || (yValue > node.StartPoint.y && yValue < node.EndPoint.y)))
                        {
                            Players[PlayerCounter].DrawShape(i: i)
                            Players[PlayerCounter].ClearLines()
                            break
                        }
                    }
                }

                i += 1

            }
            
            Players[PlayerCounter].FadeOutLine(theLine: lineStruct)
        }
    }

    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        for t in touches
        {
            var PlayerCount = 0

            for p in Players
            {
                if (t.hashValue == p.Address)
                {
                    if (p.lineNodes.count > 0)
                    {
                        p.DrawShape(i: -1)
                        p.ClearLines()
                    }

                    Players.remove(at: PlayerCount)
                    break
                }
                
                PlayerCount += 1
            }
        }
    }
}
